// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/files/scoped_temp_dir.h"

#include "base/file_util.h"
#include "base/logging.h"

namespace base {

ScopedTempDir::ScopedTempDir() {
}

ScopedTempDir::~ScopedTempDir() {
  if (!path_.empty() && !Delete())
    DLOG(WARNING) << "Could not delete temp dir in dtor.";
}

bool ScopedTempDir::CreateUniqueTempDir() {
  if (!path_.empty())
    return false;

  // This "scoped_dir" prefix is only used on Windows and serves as a template
  // for the unique name.
  if (!file_util::CreateNewTempDirectory(FILE_PATH_LITERAL("scoped_dir"),
                                         &path_))
    return false;

  return true;
}

bool ScopedTempDir::CreateUniqueTempDirUnderPath(const FilePath& base_path) {
  if (!path_.empty())
    return false;

  // If |base_path| does not exist, create it.
  if (!file_util::CreateDirectory(base_path))
    return false;

  // Create a new, uniquely named directory under |base_path|.
  if (!file_util::CreateTemporaryDirInDir(
          base_path,
          FILE_PATH_LITERAL("scoped_dir_"),
          &path_))
    return false;

  return true;
}

bool ScopedTempDir::Set(const FilePath& path) {
  if (!path_.empty())
    return false;

  if (!file_util::DirectoryExists(path) &&
      !file_util::CreateDirectory(path))
    return false;

  path_ = path;
  return true;
}

bool ScopedTempDir::Delete() {
  if (path_.empty())
    return false;

  bool ret = file_util::Delete(path_, true);
  if (ret) {
    // We only clear the path if deleted the directory.
    path_.clear();
  }

  return ret;
}

FilePath ScopedTempDir::Take() {
  FilePath ret = path_;
  path_ = FilePath();
  return ret;
}

bool ScopedTempDir::IsValid() const {
  return !path_.empty() && file_util::DirectoryExists(path_);
}

}  // namespace base
