module ALPM
  module Errno
  %w{
    MEMORY
    SYSTEM
    BADPERMS
    NOT_A_FILE
    NOT_A_DIR
    WRONG_ARGS
    DISK_SPACE
    HANDLE_NULL
    HANDLE_NOT_NULL
    HANDLE_LOCK
    DB_OPEN
    DB_CREATE
    DB_NULL
    DB_NOT_NULL
    DB_NOT_FOUND
    DB_INVALID
    DB_INVALID_SIG
    DB_VERSION
    DB_WRITE
    DB_REMOVE
    SERVER_BAD_URL
    SERVER_NONE
    TRANS_NOT_NULL
    TRANS_NULL
    TRANS_DUP_TARGET
    TRANS_NOT_INITIALIZED
    TRANS_NOT_PREPARED
    TRANS_ABORT
    TRANS_TYPE
    TRANS_NOT_LOCKED
    TRANS_HOOK_FAILED
    PKG_NOT_FOUND
    PKG_IGNORED
    PKG_INVALID
    PKG_INVALID_CHECKSUM
    PKG_INVALID_SIG
    PKG_MISSING_SIG
    PKG_OPEN
    PKG_CANT_REMOVE
    PKG_INVALID_NAME
    PKG_INVALID_ARCH
    PKG_REPO_NOT_FOUND
    SIG_MISSING
    SIG_INVALID
    DLT_INVALID
    DLT_PATCHFAILED
    UNSATISFIED_DEPS
    CONFLICTING_DEPS
    FILE_CONFLICTS
    RETRIEVE
    INVALID_REGEX
    LIBARCHIVE
    LIBCURL
    EXTERNAL_DOWNLOAD
    GPGME
  }.each_with_index { |n,i| const_set(n,i+1) }
  end

  module SigLevel
    PACKAGE = (1 << 0)
    PACKAGE_OPTIONAL = (1 << 1)
    PACKAGE_MARGINAL_OK = (1 << 2)
    PACKAGE_UNKNOWN_OK = (1 << 3)

    DATABASE = (1 << 10)
    DATABASE_OPTIONAL = (1 << 11)
    DATABASE_MARGINAL_OK = (1 << 12)
    DATABASE_UNKNOWN_OK = (1 << 13)

    USE_DEFAULT = (1 << 31)
  end
end
