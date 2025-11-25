
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#ifdef _WIN32
#include <direct.h>
#endif

// ---------------------- Utilities ----------------------

void remove_newline(char *str) { str[strcspn(str, "\n")] = '\0'; }

int is_empty(const char *s) { return s[0] == '\0'; }

int is_dot(const char *s) { return strcmp(s, ".") == 0; }

int directory_exists(const char *path) {
  struct stat st;
  return (stat(path, &st) == 0 && S_ISDIR(st.st_mode));
}

// ---------------------- Project Struct ----------------------

typedef struct {
  char root_path[200];
  char folder_name[200];
} project_t;

// ---------------------- Path Builder ----------------------

void get_folder_path(project_t *project, char *buffer, int size) {

  // Case 1: blank → "./folder"
  if (is_empty(project->root_path)) {
    snprintf(buffer, size, "./%s", project->folder_name);
    return;
  }

  // Case 2: "." → "./folder"
  if (is_dot(project->root_path)) {
    snprintf(buffer, size, "./%s", project->folder_name);
    return;
  }

  // Case 3: root ends with "/"
  int last = strlen(project->root_path) - 1;
  if (last >= 0 && project->root_path[last] == '/') {
    snprintf(buffer, size, "%s%s", project->root_path, project->folder_name);
    return;
  }

  // Case 4: normal path → add "/"
  snprintf(buffer, size, "%s/%s", project->root_path, project->folder_name);
}

// ---------------------- Steps ----------------------

void process_step_1(project_t *project) {
  printf("Enter root path (blank or '.' = current directory): ");
  fgets(project->root_path, sizeof(project->root_path), stdin);

  printf("Enter folder name: ");
  fgets(project->folder_name, sizeof(project->folder_name), stdin);

  remove_newline(project->root_path);
  remove_newline(project->folder_name);

  printf("Root: \"%s\"\n", project->root_path);
  printf("Folder: \"%s\"\n", project->folder_name);
}

void process_step_2(project_t *project) {
  char folder_path[300];
  get_folder_path(project, folder_path, sizeof(folder_path));

  printf("Resolved path: %s\n", folder_path);

  if (!directory_exists(folder_path)) {

#ifdef _WIN32
    _mkdir(folder_path);
#else
    mkdir(folder_path, 0777);
#endif

    printf("Created directory: %s\n", folder_path);
  } else {
    printf("Directory already exists: %s\n", folder_path);
  }
}

// ---------------------- Main ----------------------

int main(void) {
  printf("Welcome to the project setup!\n");

  project_t project = {0};

  process_step_1(&project);
  process_step_2(&project);

  printf("Done.\n");
  return EXIT_SUCCESS;
}
