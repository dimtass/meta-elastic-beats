DESCRIPTION = "Compile Elastic Stack Beats."

require elastic-beats.inc
DEPENDS = "systemd"

GO_PACKAGE = "journalbeat"