
#include "nrf5xhal/dfu.h"

void interrupts_disable(void)
{
    uint32_t interrupt_setting_mask;
    uint32_t irq;

    // Fetch the current interrupt settings.
    interrupt_setting_mask = NVIC->ISER[0];

    // Loop from interrupt 0 for disabling of all interrupts.
    for (irq = 0; irq < MAX_NUMBER_INTERRUPTS; irq++)
    {
        if (interrupt_setting_mask & (IRQ_ENABLED << irq))
        {
            // The interrupt was enabled, hence disable it.
            NVIC_DisableIRQ((IRQn_Type)irq);
        }
    }
}

void bootloader_start(void)
{
    uint32_t err_code;
    // uint16_t sys_serv_attr_len = sizeof(m_peer_data.sys_serv_attr);

    // err_code = sd_ble_gatts_sys_attr_get(conn_handle,
    //                                      m_peer_data.sys_serv_attr,
    //                                      &sys_serv_attr_len,
    //                                      BLE_GATTS_SYS_ATTR_FLAG_SYS_SRVCS);
    // if (err_code != NRF_SUCCESS)
    // {
    //     // Any error at this stage means the system service attributes could not be fetched.
    //     // This means the service changed indication cannot be sent in DFU mode, but connection
    //     // is still possible to establish.
    // }

    // m_reset_prepare();

    err_code = sd_power_gpregret_set(BOOTLOADER_DFU_START);
    APP_ERROR_CHECK(err_code);

    sd_softdevice_disable();
    APP_ERROR_CHECK(err_code);

    sd_softdevice_vector_table_base_set(NRF_UICR->BOOTLOADERADDR);
    APP_ERROR_CHECK(err_code);

    // dfu_app_peer_data_set(conn_handle);

    NVIC_ClearPendingIRQ(SWI2_IRQn);
    interrupts_disable();
    bootloader_util_app_start(NRF_UICR->BOOTLOADERADDR);
}
