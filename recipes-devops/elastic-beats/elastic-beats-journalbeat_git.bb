DESCRIPTION = "Compile Elastic journalbeat."

require elastic-beats.inc
PV = "7.15.2"
SRCBRANCH = "7.15"
SRCREV = "fd322dad6ceafec40c84df4d2a0694ea357d16cc"

DEPENDS = "systemd"

GO_PACKAGE = "journalbeat"
