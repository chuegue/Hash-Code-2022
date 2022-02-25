#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "List.h"
#define MAX_CHAR_LENGTH 512
typedef struct
{
    char *name;
    int level;
} Skill;

typedef struct
{
    char *name;
    int n_skills;
    Skill *skills;
} Contributor;

typedef struct
{
    char *name;
    int duration;
    int score;
    int best_before;
    int n_roles;
    Skill *roles;
} Project;

int n_contributors, n_projects;

void Free_Contributors(Contributor *contributors)
{
    for (int i = 0; i < n_contributors; i++)
    {
        free(contributors[i].name);
        for (int j = 0; j < contributors[i].n_skills; j++)
        {
            free(contributors[i].skills[j].name);
        }
        free(contributors[i].skills);
    }
    free(contributors);
}

void Free_Projects(Project *projects)
{
    for (int i = 0; i < n_projects; i++)
    {
        free(projects[i].name);
        for (int j = 0; j < projects[i].n_roles; j++)
        {
            free(projects[i].roles[j].name);
        }
        free(projects[i].roles);
    }
    free(projects);
}

void Print_Contributors(Contributor *contributors)
{
    for (int i = 0; i < n_contributors; i++)
    {
        printf("Name of contributor: %s\n", contributors[i].name);
        for (int j = 0; j < contributors[i].n_skills; j++)
        {
            printf("\t%s: %i\n", contributors[i].skills[j].name, contributors[i].skills[j].level);
        }
        printf("\n");
    }
}

void Print_Projects(Project *projects)
{
    for (int i = 0; i < n_projects; i++)
    {
        printf("Name of project: %s. Duration: %i. Score: %i. Best before: %i.\n", projects[i].name, projects[i].duration, projects[i].score, projects[i].best_before);
        for (int j = 0; j < projects[i].n_roles; j++)
        {
            printf("\t%s: %i\n", projects[i].roles[j].name, projects[i].roles[j].level);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[])
{
    assert(argc == 2 && "Missing input file. Please provide argument");
    char line[MAX_CHAR_LENGTH];
    char delim[] = " ";
    FILE *fp = fopen(argv[1], "r");
    assert(fgets(line, MAX_CHAR_LENGTH, fp));
    n_contributors = atoi(strtok(line, delim));
    n_projects = atoi(strtok(NULL, delim));
    Contributor *contributors = (Contributor *)malloc(n_contributors * sizeof(Contributor));
    Project *projects = (Project *)malloc(n_projects * sizeof(Project));
    for (int con = 0; con < n_contributors; con++)
    {
        int n_skills;
        char name[32];
        assert(fscanf(fp, "%s %i", name, &n_skills));
        contributors[con].n_skills = n_skills;
        contributors[con].name = (char *)malloc((strlen(name) + 1) * sizeof(char));
        strcpy(contributors[con].name, name);
        contributors[con].skills = (Skill *)malloc(n_skills * sizeof(Skill));
        for (int sk = 0; sk < n_skills; sk++)
        {
            int level;
            assert(fscanf(fp, "%s %i", name, &level));
            contributors[con].skills[sk].name = (char *)malloc((strlen(name) + 1) * sizeof(char));
            strcpy(contributors[con].skills[sk].name, name);
            contributors[con].skills[sk].level = level;
        }
    }
    for (int pr = 0; pr < n_projects; pr++)
    {
        char name[32];
        int duration, score, best_before, n_roles;
        assert(fscanf(fp, "%s %i %i %i %i", name, &duration, &score, &best_before, &n_roles));
        projects[pr].name = (char *)malloc((strlen(name) + 1) * sizeof(char));
        strcpy(projects[pr].name, name);
        projects[pr].duration = duration;
        projects[pr].score = score;
        projects[pr].best_before = best_before;
        projects[pr].n_roles = n_roles;
        projects[pr].roles = (Skill *)malloc(n_roles * sizeof(Skill));
        for (int rol = 0; rol < n_roles; rol++)
        {
            int level;
            assert(fscanf(fp, "%s %i", name, &level));
            projects[pr].roles[rol].name = (char *)malloc((strlen(name) + 1) * sizeof(char));
            strcpy(projects[pr].roles[rol].name, name);
            projects[pr].roles[rol].level = level;
        }
    }
    Print_Contributors(contributors);
    Print_Projects(projects);
    Free_Contributors(contributors);
    Free_Projects(projects);
    fclose(fp);
    return 0;
}