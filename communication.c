#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "space_mission.h"

int add_communication(MissionControl* system, int mission_id, const char* timestamp,
                     MessagePriority priority, const char* message) {

    if (!system || !timestamp || !message)
        return -1;

    if (timestamp[0] == '\0' || message[0] == '\0')
        return -1;

    if (!is_valid_timestamp_format(timestamp))
        return -1;

    if (!(priority == ROUTINE || priority == URGENT || priority == EMERGENCY))
        return -1;

    Mission* m = NULL;

    for (int i = 0; i < system->mission_count; i++) {
        if (system->missions[i].mission_id == mission_id) {
            m = &system->missions[i];
            break;
        }
    }

    if (!m) return -1;

    if (!m->communications) {
        m->communications = calloc(INITIAL_COMM_CAPACITY, sizeof(CommLog));
        if (!m->communications) return -1;

        m->comm_capacity = INITIAL_COMM_CAPACITY;
        m->comm_count = 0;
    }

    if (m->comm_count >= m->comm_capacity) {
        int new_capacity = m->comm_capacity * 2;
        CommLog* resized = realloc(m->communications, new_capacity * sizeof(CommLog));
        if (!resized) return -1;

        memset(resized + m->comm_capacity, 0,
               (new_capacity - m->comm_capacity) * sizeof(CommLog));

        m->communications = resized;
        m->comm_capacity = new_capacity;
    }

    CommLog* entry = &m->communications[m->comm_count];

    entry->log_id = m->comm_count + 1;

    strncpy(entry->timestamp, timestamp, sizeof(entry->timestamp) - 1);
    entry->timestamp[sizeof(entry->timestamp) - 1] = '\0';

    strncpy(entry->message, message, sizeof(entry->message) - 1);
    entry->message[sizeof(entry->message) - 1] = '\0';

    entry->priority = priority;
    entry->acknowledged = 0;

    m->comm_count++;

    return 0;
}
