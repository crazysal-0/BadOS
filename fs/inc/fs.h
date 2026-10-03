#pragma once

#include "folder.h"

void bfs_init(void);

Folder* bfs_root(void);

File* bfs_create_file(Folder* folder, const char* name, const char* extension);

Folder* bfs_create_folder(Folder* parent, const char* name);

void bfs_write_file(File* file, const char* contents);

File* bfs_find_file(Folder* folder, const char* name);

void bfs_ls(Folder* folder);
void bfs_pwd(Folder* folder);