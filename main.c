
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#ifdef _WIN32
#include <direct.h>
#endif

// Colors
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define CYAN "\033[36m"
#define BOLD "\033[1m"

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

  if (is_empty(project->root_path) || is_dot(project->root_path)) {
    snprintf(buffer, size, "./%s", project->folder_name);
    return;
  }

  int last = strlen(project->root_path) - 1;
  if (last >= 0 && project->root_path[last] == '/') {
    snprintf(buffer, size, "%s%s", project->root_path, project->folder_name);
    return;
  }

  snprintf(buffer, size, "%s/%s", project->root_path, project->folder_name);
}

void section(const char *title) {
  printf("\n" BLUE "--------------------------------------------\n" RESET);
  printf(BOLD "%s\n" RESET, title);
  printf(BLUE "--------------------------------------------\n" RESET);
}

void process_step_1(project_t *project) {
  section("🚀 maker-cli — Project Setup");

  section("📂 Step 1: Enter Project Details");

  printf(YELLOW "➤ Root path (blank or '.' = current directory): " RESET);
  fgets(project->root_path, sizeof(project->root_path), stdin);

  printf(YELLOW "➤ Folder name: " RESET);
  fgets(project->folder_name, sizeof(project->folder_name), stdin);

  remove_newline(project->root_path);
  remove_newline(project->folder_name);

  printf("\n📁 Root: \"%s\"\n", project->root_path);
  printf("📁 Folder: \"%s\"\n", project->folder_name);
}

void process_step_2(project_t *project) {
  section("🛠 Step 2: Creating Project Folder");

  char folder_path[300];
  get_folder_path(project, folder_path, sizeof(folder_path));

  printf("📌 Resolved path: %s\n", folder_path);

  if (!directory_exists(folder_path)) {

#ifdef _WIN32
    _mkdir(folder_path);
#else
    mkdir(folder_path, 0777);
#endif

    printf(GREEN "✔ Created directory: %s\n" RESET, folder_path);
  } else {
    printf(YELLOW "⚠ Directory already exists. Skipping.\n" RESET);
  }
}

void place_file(project_t *project, const char *type) {
  char folder_path[300];
  get_folder_path(project, folder_path, sizeof(folder_path));

  char command[500];
  const char *repo = strcmp(type, "ts") == 0
                         ? "https://github.com/Hayat4144/folder-cleaner.git"
                         : "https://github.com/Hayat4144/text-editor.git";

  snprintf(command, sizeof(command), "git clone \"%s\" \"%s\"", repo,
           folder_path);

  printf("\n🔽 Executing: %s\n", command);

  int result = system(command);

  if (result != 0)
    printf(RED "❌ Git clone failed\n" RESET);
  else
    printf(GREEN "✔ Clone success\n" RESET);
}

void process_step_3(project_t *project) {
  section("💻 Step 3: Choose Language");

  printf("→ 1. JavaScript\n");
  printf("→ 2. TypeScript\n");

  printf(YELLOW "➤ Enter 1/2 or js/ts: " RESET);

  char input[20];
  fgets(input, sizeof(input), stdin);
  remove_newline(input);

  if (strcmp(input, "1") == 0 || strcmp(input, "js") == 0) {
    printf(GREEN "\n✨ JavaScript selected\n" RESET);
    place_file(project, "js");

  } else if (strcmp(input, "2") == 0 || strcmp(input, "ts") == 0) {
    printf(GREEN "\n✨ TypeScript selected\n" RESET);
    place_file(project, "ts");

  } else {
    printf(RED "❌ Invalid choice\n" RESET);
  }
}

// ---------------------- Main ----------------------

int main(void) {
  project_t project = {0};

  process_step_1(&project);
  process_step_2(&project);
  process_step_3(&project);

  printf(GREEN "\n🎉 Done. Your project is ready!\n" RESET);
  return EXIT_SUCCESS;
}
