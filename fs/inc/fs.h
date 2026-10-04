#pragma once

#include "folder.h"
#include "stdbool.h"
#include "stddef.h"

void fs_init(void);

Folder* fs_root(void);

File* fs_create_file(Folder* folder, const char* name, const char* extension);

Folder* fs_create_folder(Folder* parent, const char* name);

Folder* fs_find_folder(Folder* folder, const char* name);

File* fs_find_file(Folder* folder, const char* name);

bool fs_remove_folder(Folder* parent, const char* name);

bool fs_remove_file(Folder* folder, const char* name);

void fs_write_file(File* file, const void* contents, size_t size);

void fs_ls(Folder* folder);

void fs_pwd(Folder* folder);

void fs_exec(File* file);