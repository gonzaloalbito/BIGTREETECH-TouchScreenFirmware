#include "FeatureSettings.h"
#include "includes.h"

#ifndef MENU_LIST_MODE

    MENUITEMS featureSettingsItems = {
    // title
    LABEL_FEATURE_SETTINGS,
    // icon                       label
    {
      {ICON_BACKGROUND,           LABEL_BACKGROUND},
      {ICON_BACKGROUND,           LABEL_BACKGROUND},
      {ICON_BACKGROUND,           LABEL_BACKGROUND},
      {ICON_BACKGROUND,           LABEL_BACKGROUND},
      {ICON_BACKGROUND,           LABEL_BACKGROUND},
      {ICON_BACKGROUND,           LABEL_BACKGROUND},
      {ICON_BACKGROUND,           LABEL_BACKGROUND},
      {ICON_BACK,                 LABEL_BACK},}
    };

    #define ITEM_PS_ON_NUM 2
    const ITEM itemPowerOff[ITEM_PS_ON_NUM] = {
    // icon                       label
      {ICON_POWER_SUPPLY,         LABEL_MANUAL_SHUT_DOWN},
      {ICON_POWER_SUPPLY,         LABEL_AUTO_SHUT_DOWN},
    };
    const  u8 item_power_off[ITEM_PS_ON_NUM] = {0, 1};
    static u8  item_power_off_i = 0;
      
    #ifdef FIL_RUNOUT_PIN
      #define ITEM_RUNOUT_NUM 3
      const ITEM itemRunout[ITEM_RUNOUT_NUM] = {
      // icon                       label
        {ICON_RUNOUT,               LABEL_RUNOUT_OFF},
        {ICON_RUNOUT,               LABEL_RUNOUT_ON},
        {ICON_RUNOUT,               LABEL_SMART_RUNOUT_ON},
      };
      const  u8 item_runout[ITEM_RUNOUT_NUM] = {FILAMENT_RUNOUT_OFF, FILAMENT_RUNOUT_ON, FILAMENT_SMART_RUNOUT_ON};
      static u8  item_runout_i = 0;
    #endif

    #ifdef LED_color_PIN
      #define LED_color_NUM 9
       const ITEM itemLedcolor[LED_color_NUM] = {
       // icon                       label
         {ICON_LEDCOLOR,             LABEL_OFF},
         {ICON_LEDCOLOR,             LABEL_WHITE},
         {ICON_LEDCOLOR,             LABEL_RED},
         {ICON_LEDCOLOR,             LABEL_ORANGE},
         {ICON_LEDCOLOR,             LABEL_YELLOW},
         {ICON_LEDCOLOR,             LABEL_GREEN},  
         {ICON_LEDCOLOR,             LABEL_BLUE},
         {ICON_LEDCOLOR,             LABEL_INDIGO},
         {ICON_LEDCOLOR,             LABEL_VIOLET},
       };

       const  uint32_t led_color[LED_color_NUM] = {
                                               LED_OFF,
                                               LED_WHITE,
                                               LED_RED,
                                               LED_ORANGE,
                                               LED_YELLOW,
                                               LED_GREEN,
                                               LED_BLUE,
                                               LED_INDIGO,
                                               LED_VIOLET
                                               };
       //////////////
       static u8  item_ledcolor_i = 0;
     #endif

    void menuFeatureSettings(void)
    {
      KEY_VALUES key_num = KEY_IDLE;
      SETTINGS now = infoSettings;

      for(u8 i=0; i<ITEM_PS_ON_NUM; i++)
      {
        if(infoSettings.auto_off == item_power_off[i])
        {
          item_power_off_i = i;
          featureSettingsItems.items[KEY_ICON_0] = itemPowerOff[item_power_off_i];
        }
      }
      
      #ifdef FIL_RUNOUT_PIN
      for(u8 i=0; i<ITEM_RUNOUT_NUM; i++)
      {
        if(infoSettings.runout == item_runout[i])
        {
          item_runout_i = i;
          featureSettingsItems.items[KEY_ICON_1] = itemRunout[item_runout_i];
        }
      }
      #endif
      
      #ifdef LED_color_PIN
      for(u8 i=0; i<LED_color_NUM; i++)
      {
        if(infoSettings.led_color == led_color[i])
        {
          item_ledcolor_i = i;
          featureSettingsItems.items[KEY_ICON_2] = itemLedcolor[item_ledcolor_i];
        }
      }
      #endif
      
      menuDrawPage(&featureSettingsItems);

      while(infoMenu.menu[infoMenu.cur] == menuFeatureSettings)
      {
        key_num = menuKeyGetValue();
        switch(key_num)
        {
          #ifdef FIL_RUNOUT_PIN
          case KEY_ICON_0:
            item_power_off_i = (item_power_off_i + 1) % ITEM_PS_ON_NUM;                
            featureSettingsItems.items[key_num] = itemPowerOff[item_power_off_i];
            menuDrawItem(&featureSettingsItems.items[key_num], key_num);
            infoSettings.auto_off = item_power_off[item_power_off_i];
            break;
          #endif
          
          #ifdef FIL_RUNOUT_PIN
          case KEY_ICON_1:
            item_runout_i = (item_runout_i + 1) % ITEM_RUNOUT_NUM;                
            featureSettingsItems.items[key_num] = itemRunout[item_runout_i];
            menuDrawItem(&featureSettingsItems.items[key_num], key_num);
            infoSettings.runout = item_runout[item_runout_i];
            break;
          #endif
            
          #ifdef LED_color_PIN
          case KEY_ICON_2:
            item_ledcolor_i = (item_ledcolor_i + 1) % LED_color_NUM;                
            featureSettingsItems.items[key_num] = itemLedcolor[item_ledcolor_i];
            menuDrawItem(&featureSettingsItems.items[key_num], key_num);
            infoSettings.led_color = led_color[item_ledcolor_i];
            ws2812_send_DAT(led_color[item_ledcolor_i]);
            break;
          #endif
          
          case KEY_ICON_7:
            infoMenu.cur--;
            break;
          
          default:
            break;
        }
        loopProcess();		
      }

      if(memcmp(&now, &infoSettings, sizeof(SETTINGS)))
      {
        storePara();
      }
    }

#else

    LISTITEMS featureSettingsItems = {
    // title
    LABEL_FEATURE_SETTINGS,
    // icon                 ItemType      Item Title        item value text(only for custom value)
    {
      {ICONCHAR_BACKGROUND, LIST_LABEL,  LABEL_BACKGROUND, LABEL_BACKGROUND},
      {ICONCHAR_BACKGROUND, LIST_LABEL,  LABEL_BACKGROUND, LABEL_BACKGROUND},
      {ICONCHAR_BACKGROUND, LIST_LABEL,  LABEL_BACKGROUND, LABEL_BACKGROUND},
      {ICONCHAR_BACKGROUND, LIST_LABEL,  LABEL_BACKGROUND, LABEL_BACKGROUND},
      {ICONCHAR_BACKGROUND, LIST_LABEL,  LABEL_BACKGROUND, LABEL_BACKGROUND},
      {ICONCHAR_PAGEUP,     LIST_LABEL,  LABEL_BACKGROUND, LABEL_BACKGROUND},
      {ICONCHAR_PAGEDOWN,   LIST_LABEL,  LABEL_BACKGROUND, LABEL_BACKGROUND},
      {ICONCHAR_BACK,       LIST_LABEL,  LABEL_BACKGROUND, LABEL_BACKGROUND},}
    };

//
//setup item states
//

    #define TOGGLE_NUM   2
    const uint16_t toggleitem[TOGGLE_NUM] = {ICONCHAR_TOGGLE_OFF,ICONCHAR_TOGGLE_ON};

    
    #ifdef FIL_RUNOUT_PIN
      #define ITEM_RUNOUT_NUM 3
      const LABEL itemRunout[ITEM_RUNOUT_NUM] = {
                                                  //item value text(only for custom value)
                                                  LABEL_OFF,
                                                  LABEL_ON,
                                                  LABEL_SMART,
                                                };

    #endif
    
    #define ITEM_SPEED_NUM 3
    const LABEL itemMoveSpeed[ITEM_SPEED_NUM] = {
                                                  //item value text(only for custom value)
                                                  LABEL_NORMAL_SPEED,
                                                  LABEL_SLOW_SPEED,
                                                  LABEL_FAST_SPEED,
                                                };
    const  u8 item_movespeed[ITEM_SPEED_NUM] = {LABEL_NORMAL_SPEED, LABEL_SLOW_SPEED, LABEL_FAST_SPEED};

    #ifdef LED_color_PIN
      #define LED_color_NUM 9
      const LABEL itemLedcolor[LED_color_NUM] = {
                                                  //label
                                                  LABEL_OFF,
                                                  LABEL_WHITE,
                                                  LABEL_RED,
                                                  LABEL_ORANGE,
                                                  LABEL_YELLOW,
                                                  LABEL_GREEN,
                                                  LABEL_BLUE,
                                                  LABEL_INDIGO,
                                                  LABEL_VIOLET,
                                                };

      const  uint32_t led_color[LED_color_NUM] = {
                                                  LED_OFF,
                                                  LED_WHITE,
                                                  LED_RED,
                                                  LED_ORANGE,
                                                  LED_YELLOW,
                                                  LED_GREEN,
                                                  LED_BLUE,
                                                  LED_INDIGO,
                                                  LED_VIOLET
                                                  };

    #endif
//
//add key number index of the items
//
    typedef enum
    {
      SKEY_HIDEACK = 0,
      SKEY_INVERT_Y,
      SKEY_INVERT_Z,
      #ifdef PS_ON_PIN
        SKEY_POWER,
      #endif
      #ifdef FIL_RUNOUT_PIN
        SKEY_RUNOUT,
      #endif
      SKEY_SPEED,
      SKEY_STARTGCODE,
      SKEY_ENDGCODE,
      SKEY_PERSISTENTINFO,
      #ifdef LED_color_PIN
      SKEY_KNOB,
      #endif
      SKEY_COUNT //keep this always at the end
    }SKEY_LIST; 
    
    #define FE_PAGE_COUNT  (SKEY_COUNT+LISTITEM_PER_PAGE-1)/LISTITEM_PER_PAGE
    int fe_cur_page = 0;

//
//set item types
//
    LISTITEM settingPage[SKEY_COUNT] = {  
      {ICONCHAR_TOGGLE_ON,  LIST_TOGGLE,        LABEL_TERMINAL_ACK,       LABEL_BACKGROUND},
      {ICONCHAR_TOGGLE_ON,  LIST_TOGGLE,        LABEL_INVERT_YAXIS,       LABEL_BACKGROUND},
      {ICONCHAR_TOGGLE_ON,  LIST_TOGGLE,        LABEL_INVERT_ZAXIS,       LABEL_BACKGROUND},
      #ifdef PS_ON_PIN
      {ICONCHAR_TOGGLE_ON,  LIST_TOGGLE,        LABEL_AUTO_SHUT_DOWN,     LABEL_BACKGROUND},
      #endif
      #ifdef FIL_RUNOUT_PIN
      {ICONCHAR_BLANK,      LIST_CUSTOMVALUE,   LABEL_FILAMENT_RUNOUT,    LABEL_OFF       },
      #endif
      {ICONCHAR_BLANK,      LIST_CUSTOMVALUE,   LABEL_MOVE_SPEED,                 LABEL_NORMAL_SPEED},
      {ICONCHAR_TOGGLE_ON,  LIST_TOGGLE,        LABEL_SEND_START_GCODE,           LABEL_BACKGROUND},
      {ICONCHAR_TOGGLE_ON,  LIST_TOGGLE,        LABEL_SEND_END_GCODE,             LABEL_BACKGROUND},
      {ICONCHAR_TOGGLE_ON,  LIST_TOGGLE,        LABEL_PERSISTENT_STATUS_INFO,     LABEL_BACKGROUND},
      #ifdef LED_color_PIN
      {ICONCHAR_BLANK,      LIST_CUSTOMVALUE,   LABEL_KNOB_LED,           LABEL_OFF       },
      #endif
      
    };

//
//perform action on button press
//
    void updateFeatureSettings(uint8_t key_val)
    {
      uint8_t item_index = fe_cur_page*LISTITEM_PER_PAGE+ key_val;
      switch (item_index)
      {
        case SKEY_HIDEACK:
        infoSettings.terminalACK = (infoSettings.terminalACK + 1) % TOGGLE_NUM;
        settingPage[item_index].icon = toggleitem[infoSettings.terminalACK];
        featureSettingsItems.items[key_val] = settingPage[item_index];

        menuDrawListItem(&featureSettingsItems.items[key_val], key_val);
        break;

        case SKEY_INVERT_Y:
        infoSettings.invert_yaxis = (infoSettings.invert_yaxis + 1) % TOGGLE_NUM;
        settingPage[item_index].icon = toggleitem[infoSettings.invert_yaxis];
        featureSettingsItems.items[key_val] = settingPage[item_index];

        menuDrawListItem(&featureSettingsItems.items[key_val], key_val);
        break;

        case SKEY_INVERT_Z:
        infoSettings.invert_zaxis = (infoSettings.invert_zaxis + 1) % TOGGLE_NUM;
        settingPage[item_index].icon = toggleitem[infoSettings.invert_zaxis];
        featureSettingsItems.items[key_val] = settingPage[item_index];

        menuDrawListItem(&featureSettingsItems.items[key_val], key_val);
        break;

        #ifdef PS_ON_PIN
        case SKEY_POWER:
        infoSettings.auto_off = (infoSettings.auto_off + 1) % TOGGLE_NUM;
        settingPage[item_index].icon = toggleitem[infoSettings.auto_off];
        featureSettingsItems.items[key_val] = settingPage[item_index];
        
        menuDrawListItem(&featureSettingsItems.items[key_val], key_val);
        break;
        #endif

        #ifdef FIL_RUNOUT_PIN
        case SKEY_RUNOUT:
        infoSettings.runout = (infoSettings.runout + 1) % ITEM_RUNOUT_NUM;
        settingPage[item_index].valueLabel = itemRunout[infoSettings.runout];
        featureSettingsItems.items[key_val] = settingPage[item_index];
        
        menuDrawListItem(&featureSettingsItems.items[key_val], key_val);
        break;
        #endif

        case SKEY_SPEED:
        infoSettings.move_speed = (infoSettings.move_speed + 1) % ITEM_SPEED_NUM;
        settingPage[item_index].valueLabel = itemMoveSpeed[infoSettings.move_speed];
        featureSettingsItems.items[key_val] = settingPage[item_index];

        menuDrawListItem(&featureSettingsItems.items[key_val], key_val);
        break;
        
        case SKEY_STARTGCODE:
        infoSettings.send_start_gcode = (infoSettings.send_start_gcode + 1) % TOGGLE_NUM;
        settingPage[item_index].icon = toggleitem[infoSettings.send_start_gcode];
        featureSettingsItems.items[key_val] = settingPage[item_index];

        menuDrawListItem(&featureSettingsItems.items[key_val], key_val);
        break;

        case SKEY_ENDGCODE:
        infoSettings.send_end_gcode = (infoSettings.send_end_gcode + 1) % TOGGLE_NUM;
        settingPage[item_index].icon = toggleitem[infoSettings.send_end_gcode];
        featureSettingsItems.items[key_val] = settingPage[item_index];

        menuDrawListItem(&featureSettingsItems.items[key_val], key_val);
        break;
        
        case SKEY_PERSISTENTINFO:
        infoSettings.persistent_info = (infoSettings.persistent_info + 1) % TOGGLE_NUM;
        settingPage[item_index].icon = toggleitem[infoSettings.persistent_info];
        featureSettingsItems.items[key_val] = settingPage[item_index];

        menuDrawListItem(&featureSettingsItems.items[key_val], key_val);
        break;

        #ifdef LED_color_PIN
        case SKEY_KNOB:            
        infoSettings.led_color = (infoSettings.led_color + 1) % LED_color_NUM;                
        settingPage[item_index].valueLabel = itemLedcolor[infoSettings.led_color];
        featureSettingsItems.items[key_val] = settingPage[item_index];
        ws2812_send_DAT(led_color[infoSettings.led_color]);

        menuDrawListItem(&featureSettingsItems.items[key_val], key_val);
        break;
        #endif

      default:
        break;
      }
    }

//
//load values on page change and reload
//
    void loadFeatureSettings(){
      for (uint8_t i = 0; i < LISTITEM_PER_PAGE; i++)
      {
        uint8_t item_index = fe_cur_page*LISTITEM_PER_PAGE + i;
        switch (item_index)
        {
          case SKEY_HIDEACK:
            settingPage[item_index].icon = toggleitem[infoSettings.terminalACK];
            featureSettingsItems.items[i] = settingPage[item_index];
            break;

          case SKEY_INVERT_Y:
            settingPage[item_index].icon = toggleitem[infoSettings.invert_yaxis];
            featureSettingsItems.items[i] = settingPage[item_index];
            break;

          case SKEY_INVERT_Z:
            settingPage[item_index].icon = toggleitem[infoSettings.invert_zaxis];
            featureSettingsItems.items[i] = settingPage[item_index];
            break;

          #ifdef PS_ON_PIN
            case SKEY_POWER:
            settingPage[item_index].icon = toggleitem[infoSettings.auto_off];
            featureSettingsItems.items[i] = settingPage[item_index];
            break;
          #endif

          #ifdef FIL_RUNOUT_PIN
            case SKEY_RUNOUT:
            settingPage[item_index].valueLabel = itemRunout[infoSettings.runout];
            featureSettingsItems.items[i] = settingPage[item_index];
            break;
          #endif

          case SKEY_SPEED:
            settingPage[item_index].valueLabel = itemMoveSpeed[infoSettings.move_speed];
            featureSettingsItems.items[i] = settingPage[item_index];
            break;

          case SKEY_STARTGCODE:
            settingPage[item_index].icon  = toggleitem[infoSettings.send_start_gcode];
            featureSettingsItems.items[i] = settingPage[item_index];
            break;

          case SKEY_ENDGCODE:
            settingPage[item_index].icon  = toggleitem[infoSettings.send_end_gcode];
            featureSettingsItems.items[i] = settingPage[item_index];
            break;

          case SKEY_PERSISTENTINFO:
            settingPage[item_index].icon  = toggleitem[infoSettings.persistent_info];
            featureSettingsItems.items[i] = settingPage[item_index];
            break;

          #ifdef LED_color_PIN
            case SKEY_KNOB:                           
            settingPage[item_index].valueLabel = itemLedcolor[infoSettings.led_color];
            featureSettingsItems.items[i] = settingPage[item_index];
            break;
          #endif

          default:
            settingPage[item_index].icon = ICONCHAR_BACKGROUND;
            featureSettingsItems.items[i] = settingPage[item_index];
          break;
        }
     }
      // set page up down button according to page count and current page
      if (SKEY_COUNT <= LISTITEM_PER_PAGE)
      {
        featureSettingsItems.items[5].icon = ICONCHAR_BACKGROUND;
        featureSettingsItems.items[6].icon = ICONCHAR_BACKGROUND;
      }
      else
      {
        if(fe_cur_page == 0){
          featureSettingsItems.items[5].icon = ICONCHAR_BACKGROUND;
          featureSettingsItems.items[6].icon = ICONCHAR_PAGEDOWN;
        }
        else if(fe_cur_page == (FE_PAGE_COUNT-1)){
          featureSettingsItems.items[5].icon = ICONCHAR_PAGEUP;
          featureSettingsItems.items[6].icon = ICONCHAR_BACKGROUND;
        }
        else
        {
          featureSettingsItems.items[5].icon = ICONCHAR_PAGEUP;
          featureSettingsItems.items[6].icon = ICONCHAR_PAGEDOWN;
        }
      }
      //menuDrawListItem(&featureSettingsItems.items[5],5);
      //menuDrawListItem(&featureSettingsItems.items[6],6);
      
    }


    void menuFeatureSettings(void)
    {
      KEY_VALUES key_num = KEY_IDLE;
      SETTINGS now = infoSettings;
      fe_cur_page = 0;
      loadFeatureSettings();
      menuDrawListPage(&featureSettingsItems);

      while (infoMenu.menu[infoMenu.cur] == menuFeatureSettings)
      {
        key_num = menuKeyGetValue();
        switch (key_num)
        {
        case KEY_ICON_5:
          if(FE_PAGE_COUNT > 1){
            if (fe_cur_page > 0){
              fe_cur_page--;
              loadFeatureSettings();
              menuRefreshListPage();
            }
          }
          break;

        case KEY_ICON_6:
          if(FE_PAGE_COUNT > 1){
            if (fe_cur_page < FE_PAGE_COUNT - 1){
              fe_cur_page++;
              loadFeatureSettings();
              menuRefreshListPage();
            }
          }
          break;

        case KEY_ICON_7:
          infoMenu.cur--;
          break;
        default:
          if(key_num < LISTITEM_PER_PAGE){
          updateFeatureSettings(key_num);
          menuDrawListItem(&featureSettingsItems.items[key_num],key_num);
          }
          break;
        }

      loopProcess();		
    }

      if(memcmp(&now, &infoSettings, sizeof(SETTINGS)))
      {
        storePara();
      }
    }

#endif
