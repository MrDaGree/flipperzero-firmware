#include "../infrared_i.h"

#include <dolphin/dolphin.h>

void infrared_scene_learn_done_on_enter(void* context) {
    Infrared* infrared = context;
    Popup* popup = infrared->popup;

    popup_set_icon(popup, 32, 5, &I_DolphinNice_96x59);
    DOLPHIN_DEED(DolphinDeedIrSave);

    if(infrared->app_state.is_learning_new_remote) {
        popup_set_header(popup, "New remote\ncreated!", 0, 0, AlignLeft, AlignTop);
    } else {
        popup_set_header(popup, "Saved!", 5, 7, AlignLeft, AlignTop);
    }

    popup_set_callback(popup, infrared_popup_timeout_callback);
    popup_set_context(popup, context);
    popup_set_timeout(popup, 1500);
    popup_enable_timeout(popup);

    view_dispatcher_switch_to_view(infrared->view_dispatcher, InfraredViewPopup);
}

bool infrared_scene_learn_done_on_event(void* context, SceneManagerEvent event) {
    Infrared* infrared = context;
    bool consumed = false;

    if(event.type == SceneManagerEventTypeCustom) {
        if(event.event == InfraredCustomEventTypePopupTimeout) {
            scene_manager_next_scene(infrared->scene_manager, InfraredSceneRemote);
            consumed = true;
        }
    }

    return consumed;
}

void infrared_scene_learn_done_on_exit(void* context) {
    Infrared* infrared = context;
    infrared->app_state.is_learning_new_remote = false;
    popup_set_header(infrared->popup, NULL, 0, 0, AlignLeft, AlignTop);
}
