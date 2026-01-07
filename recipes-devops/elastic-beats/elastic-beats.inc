DESCRIPTION = "Compile Elastic Stack Beats."
HOMEPAGE = "https://github.com/elastic/beats"
AUTHOR = "Dimitris Tassopoulos <dimtass@gmail.com>, Muzammil Ahmad <muzammil.ahmad@epteck.com"

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${BEAT_FOLDER}/LICENSE.txt;md5=00294979737b05a575493ff7b723f25c"

BEATS_S = "${WORKDIR}/git"

GO_IMPORT = "github.com/elastic/beats"
GO_INSTALL = "${GO_IMPORT}"
GO_WORKDIR = "${GO_IMPORT}/${GO_PACKAGE}"
BEAT_FOLDER = "src/${GO_INSTALL}"
GO_PACKAGE ?= ""

FILESEXTRAPATHS:append = "${THISDIR}/elastic-beats:"

inherit go-mod systemd

PV = "8.4.3"
SRCBRANCH ?= "8.4"
SRCREV ?= "2b41b676ec0ac5a16a04baeb0ece2403177b9432"

RDEPENDS:${PN} += "bash"

SRC_URI = " \
        git://${GO_IMPORT}.git;protocol=https;branch=${SRCBRANCH} \
        file://${GO_PACKAGE}.yml \
        file://${GO_PACKAGE}.service \
        "

CGO_CFLAGS += "--sysroot=${STAGING_DIR_TARGET} -I${STAGING_INCDIR}"
CGO_LDFLAGS += "--sysroot=${STAGING_DIR_TARGET} -L${STAGING_LIBDIR}"


SYSTEMD_SERVICE:${PN} = "${GO_PACKAGE}.service"

do_compile[network] = "1"
do_compile:prepend() {
    export GOPROXY=https://proxy.golang.org
}

do_install() {

    install -d ${D}${bindir}/
    install -m 0755 ${B}/bin/${GO_PACKAGE} ${D}${bindir}

    install -d ${D}${datadir}/${GO_PACKAGE}/bin
    install -m 0755 ${B}/bin/${GO_PACKAGE} ${D}${datadir}/${GO_PACKAGE}/bin/

    install -d ${D}${sysconfdir}/${GO_PACKAGE}
    install -m 0755 ${WORKDIR}/${GO_PACKAGE}.yml ${D}${sysconfdir}/${GO_PACKAGE}/${GO_PACKAGE}.yml

    install -d ${D}${systemd_unitdir}/system
    install -m 0644 ${WORKDIR}/${GO_PACKAGE}.service ${D}${systemd_unitdir}/system/

}

FILES:${PN} += " \
        ${datadir} \
        ${system_unitdir} \
        ${sysconfdir} \
"
