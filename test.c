#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Initial size for environment array
#define ENV_SIZE 100

// Custom environment array
char **custom_env;
int custom_env_size = 0;

// Function to initialize the custom environment from the system environment
void init_custom_env(char *envp[]) {
    custom_env = malloc(ENV_SIZE * sizeof(char *));
    for (int i = 0; envp[i] != NULL; i++) {
        custom_env[i] = strdup(envp[i]);  // Duplicate the environment string
        custom_env_size++;
    }
    custom_env[custom_env_size] = NULL;  // Null-terminate the array
}

// Custom setenv function to add or update an environment variable
void my_setenv(const char *key, const char *value) {
    int key_len = strlen(key);
    for (int i = 0; i < custom_env_size; i++) {
        if (strncmp(custom_env[i], key, key_len) == 0 && custom_env[i][key_len] == '=') {
            // If the key exists, update its value
            free(custom_env[i]);
            custom_env[i] = malloc(strlen(key) + strlen(value) + 2);
            sprintf(custom_env[i], "%s=%s", key, value);
            return;
        }
    }
    // If the key doesn't exist, add a new environment variable
    custom_env[custom_env_size] = malloc(strlen(key) + strlen(value) + 2);
    sprintf(custom_env[custom_env_size], "%s=%s", key, value);
    custom_env_size++;
    custom_env[custom_env_size] = NULL;  // Update the null-terminator
}

// Custom unsetenv function to remove an environment variable
void my_unsetenv(const char *key) {
    int key_len = strlen(key);
    for (int i = 0; i < custom_env_size; i++) {
        if (strncmp(custom_env[i], key, key_len) == 0 && custom_env[i][key_len] == '=') {
            // If the key is found, free the memory and shift the rest
            free(custom_env[i]);
            for (int j = i; j < custom_env_size - 1; j++) {
                custom_env[j] = custom_env[j + 1];
            }
            custom_env[--custom_env_size] = NULL;  // Update the size and null-terminate
            return;
        }
    }
}

// Function to print the custom environment
void print_custom_env() {
    printf("Custom environment:\n");
    for (int i = 0; i < custom_env_size; i++) {
        printf("%s\n", custom_env[i]);
    }
}

int main(int argc, char *argv[], char *envp[]) {
    // Initialize the custom environment with system environment
    init_custom_env(envp);

    // Example: Set and unset environment variables
    my_setenv("MY_VAR", "HelloWorld");
	my_setenv("OTHER_VAR", "HelloWorld");
    // print_custom_env();
    printf("\n");

    my_unsetenv("MY_VAR");
    print_custom_env();

    // Free allocated memory
    for (int i = 0; i < custom_env_size; i++) {
        free(custom_env[i]);
    }
    free(custom_env);

    return 0;
}