#include <stdlib.h>
#include "space_mission.h"

void free_mission_control(MissionControl* system) {
    if (!system) return;

    if (system->missions) {
        for (int i = 0; i < system->mission_count; i++) {
            if (system->missions[i].communications) {
                free(system->missions[i].communications);
                system->missions[i].communications = NULL;
            }
        }
        free(system->missions);
        system->missions = NULL;
    }

    free(system);
}
