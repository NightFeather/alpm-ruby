module ALPM
  class Package

    module InstallOrigin
      FILE    = 1
      LOCALDB = 2
      SYNCDB  = 3
    end

    module InstallReason
      EXPLICT = 0
      DEPEND  = 1
    end

    module InstallValidation
      UNKNOWN   = 0
      NONE      = 1
      MD5SUM    = 1 << 1
      SHA256SUM = 1 << 2
      SIGNATURE = 1 << 3
    end
  end
end
