
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#ifdef _WIN32
#include <direct.h>
#endif

void remove_newline(char *str) { str[strcspn(str, "\n")] = '\0'; }

int is_empty(const char *s) { return s[0] == '\0'; }

int is_dot(const char *s) { return strcmp(s, ".") == 0; }

int directory_exists(const char *path) {
  struct stat st;
  return (stat(path, &st) == 0 && S_ISDIR(st.st_mode));
}

typedef struct {
  char root_path[200];
  char folder_name[200];
} project_t;

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

void place_file(project_t *project, const char *type) {
  char folder_path[300];
  get_folder_path(project, folder_path, sizeof(folder_path)); // root + folder

  char command[500];

  const char *repo = strcmp(type, "ts") == 0
                         ? "https://github.com/Hayat4144/folder-cleaner.git"
                         : "https://github.com/Hayat4144/text-editor.git";

  snprintf(command, sizeof(command), "git clone \"%s\" \"%s\"", repo,
           folder_path);

  printf("Executing: %s\n", command);

  int result = system(command);

  if (result != 0) {
    printf("❌ Git clone failed\n");
  } else {
    printf("✔ Clone success\n");
  }
}

void process_step_3(project_t *project) {
  printf("Choose language:\n");
  printf("1. JavaScript\n");
  printf("2. TypeScript\n");
  printf("Enter 1/2 or js/ts: ");

  char input[20];
  fgets(input, sizeof(input), stdin);
  remove_newline(input);

  if (strcmp(input, "1") == 0 || strcmp(input, "js") == 0) {
    printf("JavaScript selected\n");
    place_file(project, "js");
  } else if (strcmp(input, "2") == 0 || strcmp(input, "ts") == 0) {
    printf("TypeScript selected\n");
    place_file(project, "ts");
  } else {
    printf("Invalid choice\n");
  }
}

// ---------------------- Main ----------------------

int main(void) {
  printf("Welcome to the project setup!\n");

  project_t project = {0};

  process_step_1(&project);
  process_step_2(&project);
  process_step_3(&project);

  printf("Done.\n");
  return EXIT_SUCCESS;
}
