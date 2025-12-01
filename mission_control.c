#include <stdlib.h>
#include <string.h>
#include "space_mission.h"

MissionControl* create_mission_control(int initial_capacity) {
    if (initial_capacity <= 0) return NULL;

    MissionControl* system = malloc(sizeof(MissionControl));
    if (!system) return NULL;

    system->missions = malloc(sizeof(Mission) * initial_capacity);
    if (!system->missions) {
        free(system);
        return NULL;
    }

    memset(system->missions, 0, sizeof(Mission) * initial_capacity);
    system->mission_count = 0;
    system->capacity = initial_capacity;

    return system;
}

int create_mission_with_crew(MissionControl* system, int mission_id, const char* name,
                             const char* launch_date) {
    if (!system || !name || !launch_date) return -1;
    if (mission_id <= 0) return -1;
    if (name[0] == '\0') return -1;
    if (!is_valid_date_format(launch_date)) return -1;

    for (int i = 0; i < system->mission_count; i++) {
        if (system->missions[i].mission_id == mission_id) return -1;
    }

    if (system->mission_count >= system->capacity) {
        int new_capacity = system->capacity * 2;
        Mission* new_array = realloc(system->missions, sizeof(Mission) * new_capacity);
        if (!new_array) return -1;

        size_t old_bytes = sizeof(Mission) * system->capacity;
        size_t new_bytes = sizeof(Mission) * new_capacity;
        memset((char*)new_array + old_bytes, 0, new_bytes - old_bytes);

        system->missions = new_array;
        system->capacity = new_capacity;
    }

    Mission* m = &system->missions[system->mission_count];
    memset(m, 0, sizeof(Mission));

    m->mission_id = mission_id;

    strncpy(m->mission_name, name, sizeof(m->mission_name) - 1);
    m->mission_name[sizeof(m->mission_name) - 1] = '\0';

    strncpy(m->launch_date, launch_date, sizeof(m->launch_date) - 1);
    m->launch_date[sizeof(m->launch_date) - 1] = '\0';

    m->status = PLANNED;

    m->communications = calloc(INITIAL_COMM_CAPACITY, sizeof(CommLog));
    if (!m->communications) return -1;

    m->comm_count = 0;
    m->comm_capacity = INITIAL_COMM_CAPACITY;

    system->mission_count++;
    return 0;
}
