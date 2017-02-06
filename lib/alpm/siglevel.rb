module ALPM
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