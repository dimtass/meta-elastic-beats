DESCRIPTION = "Compile naive mage"
HOMEPAGE = "https://github.com/elastic/beats/tree/master/libbeat"

inherit go native

GO_IMPORT = "github.com/magefile/mage"

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://src/${GO_IMPORT}/LICENSE;md5=02754c9de112baaa49870a35979afec1"

SRCREV = "${AUTOREV}"

GO_INSTALL = "${GO_IMPORT}"

SRC_URI = "git://${GO_IMPORT}.git;protocol=https;branch=master"

DEPENDS += "\
"