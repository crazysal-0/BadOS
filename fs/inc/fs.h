#pragma once

#include "folder.h"
#include "stdbool.h"
#include "stddef.h"

void bfs_init(void);

Folder* bfs_root(void);

File* bfs_create_file(Folder* folder, const char* name, const char* extension);

Folder* bfs_create_folder(Folder* parent, const char* name);

Folder* bfs_find_folder(Folder* folder, const char* name);

File* bfs_find_file(Folder* folder, const char* name);

bool bfs_remove_folder(Folder* parent, const char* name);

bool bfs_remove_file(Folder* folder, const char* name);

void bfs_write_file(File* file, const void* contents, size_t size);

void bfs_ls(Folder* folder);

void bfs_pwd(Folder* folder);

void bfs_exec(File* file);