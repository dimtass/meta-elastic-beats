DESCRIPTION = "Compile Elastic journalbeat."

require elastic-beats.inc
DEPENDS = "systemd"

GO_PACKAGE = "journalbeat"