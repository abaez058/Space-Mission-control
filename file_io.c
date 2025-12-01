#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "space_mission.h"

int load_missions_from_file(MissionControl* system, const char* filename) {
    if (!system || !filename) return -1;

    FILE* file = fopen(filename, "r");
    if (!file) return -1;

    int mission_count = 0;
    if (fscanf(file, "%d", &mission_count) != 1 || mission_count < 0) {
        fclose(file);
        return -1;
    }

    for (int i = 0; i < mission_count; ++i) {
        int id;
        char name[MAX_NAME_LENGTH];
        char date[MAX_DATE_LENGTH];

        if (fscanf(file, "%d %127s %31s", &id, name, date) != 3) {
            fclose(file);
            return -1;
        }

        if (id <= 0 || !is_valid_date_format(date)) {
            fclose(file);
            return -1;
        }

        if (create_mission_with_crew(system, id, name, date) != 0) {
            fclose(file);
            return -1;
        }
    }

    fclose(file);
    return 0;
}

int save_mission_report(const MissionControl* system, const char* filename) {
    if (!system || !filename) return -1;

    FILE* file = fopen(filename, "w");
    if (!file) return -1;

    fprintf(file, "=====================================\n");
    fprintf(file, " SPACE MISSION CONTROL REPORT\n");
    fprintf(file, "=====================================\n");
    fprintf(file, "Total Missions: %d\n\n", system->mission_count);

    int total_comms = 0;

    for (int i = 0; i < system->mission_count; ++i) {
        const Mission* m = &system->missions[i];

        int routine = 0, urgent = 0, emergency = 0;

        for (int c = 0; c < m->comm_count; ++c) {
            const CommLog* comm = &m->communications[c];
            if (comm->priority == ROUTINE) ++routine;
            else if (comm->priority == URGENT) ++urgent;
            else if (comm->priority == EMERGENCY) ++emergency;
        }

        total_comms += m->comm_count;

        fprintf(file, "-------------------------------------\n");
        fprintf(file, "Mission ID: %d\n", m->mission_id);
        fprintf(file, "Name: %s\n", m->mission_name);
        fprintf(file, "Launch Date: %s\n", m->launch_date);
        fprintf(file, "Status: %s\n", status_to_string(m->status));
        fprintf(file, "Total Communications: %d\n", m->comm_count);
        fprintf(file, "  Routine: %d\n", routine);
        fprintf(file, "  Urgent: %d\n", urgent);
        fprintf(file, "  Emergency: %d\n\n", emergency);
    }

    fprintf(file, "=====================================\n");
    fprintf(file, "System Total Communications: %d\n", total_comms);
    fprintf(file, "=====================================\n");

    fclose(file);
    return 0;
}
