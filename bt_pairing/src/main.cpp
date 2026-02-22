#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include <zephyr/settings/settings.h>

#include <soc.h>

//Bluetooth
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/hci.h>

LOG_MODULE_REGISTER(LOGGER);

struct k_work adv_work;

const struct bt_data ad[] = {
	BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
	BT_DATA(BT_DATA_NAME_COMPLETE, CONFIG_BT_DEVICE_NAME, sizeof(CONFIG_BT_DEVICE_NAME)),
};

const struct bt_data sd[] = {
	//BT_DATA_BYTES(BT_DATA_UUID128_ALL, BT_UUID_LBS_VAL),
};

void adv_start(struct k_work *work)
{
	int err = bt_le_adv_start(BT_LE_ADV_CONN_FAST_2, ad, ARRAY_SIZE(ad), sd, ARRAY_SIZE(sd));
	if (err) {
		LOG_ERR("Advertising failed to start (err %d)", err);
		return;
	}
	LOG_INF("Advertising successfully started");
}

static void connected(struct bt_conn *conn, uint8_t err)
{
	if (err) {
		LOG_ERR("Connection failed, err 0x%02x %s", err, bt_hci_err_to_str(err));
		return;
	}
	LOG_INF("Connected");
}

static void disconnected(struct bt_conn *conn, uint8_t reason)
{
	LOG_INF("Disconnected, reason 0x%02x %s", reason, bt_hci_err_to_str(reason));
}

//使用済みの接続オブジェクトがシステムによって接続プールに返されたときに呼び出されます。
static void recycled_cb(void)
{
	LOG_INF("Connection object available from previous conn. Disconnect is complete!");
	k_work_submit(&adv_work);
}

static void security_changed(struct bt_conn *conn, bt_security_t level, enum bt_security_err err)
{
	char addr[BT_ADDR_LE_STR_LEN];
	bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));
	if (!err) {
		LOG_INF("Security changed: %s level %u", addr, level);
	}
	else {
		LOG_ERR("Security failed: %s level %u err %d %s", addr, level, err, bt_security_err_to_str(err));
	}
}

//イベント
BT_CONN_CB_DEFINE(conn_callbacks) = {
	.connected        = connected,
	.disconnected     = disconnected,
	.recycled         = recycled_cb,
	.security_changed = security_changed,
};

static struct bt_conn_auth_cb conn_auth_callbacks = {
	.passkey_display = NULL,//passkeyの表示手段なし
	.passkey_entry = NULL,//passkeyの入力手段なし
	.passkey_confirm = NULL,//passkeyの確認手段なし
};

static void pairing_complete(struct bt_conn *conn, bool bonded)
{
	char addr[BT_ADDR_LE_STR_LEN];
	bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));
	LOG_INF("Pairing completed: %s, bonded: %d", addr, bonded);
}

static void pairing_failed(struct bt_conn *conn, enum bt_security_err reason)
{
	char addr[BT_ADDR_LE_STR_LEN];
	bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));
	LOG_INF("Pairing failed conn: %s, reason %d %s", addr, reason, bt_security_err_to_str(reason));
}

static void bond_deleted(uint8_t id, const bt_addr_le_t *peer)
{
	LOG_INF("Bond deleted");
}

static struct bt_conn_auth_info_cb conn_auth_info_callbacks = {
	.pairing_complete = pairing_complete,
	.pairing_failed = pairing_failed,
	.bond_deleted = bond_deleted,
};

int main(void)
{
	int err;
	bool option_le_unpair = false;

	//botton0(P1.13)をチェックする 押されていればoption_le_unpairをtrueにする
	//レジスタレベルでチェックする 8回連続でチェックして同じ値であることをチェックし押されていると判定する
	{
		NRF_P1->DIRCLR = (1 << 13);
		NRF_P1->PIN_CNF[13] = 
			(GPIO_PIN_CNF_PULL_Pullup << GPIO_PIN_CNF_PULL_Pos) |
			(GPIO_PIN_CNF_INPUT_Connect << GPIO_PIN_CNF_INPUT_Pos) |
			(GPIO_PIN_CNF_DIR_Input << GPIO_PIN_CNF_DIR_Pos);
		int count = 0;
		while (1) {
			if (NRF_P1->IN & (1 << 13)) {//Highならばボタンが押されていない
				if (option_le_unpair == true) {
					count = 0;
				}
				option_le_unpair = false;
			}
			else {
				if (option_le_unpair == false) {
					count = 0;
				}
				option_le_unpair = true;
			}
			count++;
			if (count >= 8) {
				break;
			}
			k_sleep(K_MSEC(1));
		}
	}

	err = bt_conn_auth_cb_register(&conn_auth_callbacks);
	if (err) {
		LOG_ERR("Failed to register authorization callbacks.");
		return 0;
	}

	err = bt_conn_auth_info_cb_register(&conn_auth_info_callbacks);
	if (err) {
		LOG_ERR("Failed to register authorization info callbacks.");
		return 0;
	}

	err = bt_enable(NULL);
	if (err) {
		LOG_ERR("Bluetooth init failed (err %d)", err);
		return 0;
	}
	LOG_INF("Bluetooth initialized");

	settings_load();
	if (option_le_unpair) {
		LOG_INF("Bluetooth Unpair");
		bt_unpair(BT_ID_DEFAULT, NULL);//全てのペアリング情報を削除
	}

	k_work_init(&adv_work, adv_start);
	k_work_submit(&adv_work);
	for (;;) {
		k_sleep(K_MSEC(250));
	}

	return 0;
}
