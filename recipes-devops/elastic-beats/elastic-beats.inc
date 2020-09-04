DESCRIPTION = "Compile Elastic Stack Beats."
HOMEPAGE = "https://github.com/elastic/beats"
AUTHOR = "Dimitris Tassopoulos <dimtass@gmail.com>"

inherit go go-mod

GO_PACKAGE ?= ""

GO_IMPORT = "github.com/elastic/beats"
GO_INSTALL = "${GO_IMPORT}/${GO_PACKAGE}"
BEAT_FOLDER = "${S}/src/${GO_INSTALL}"


LICENSE = "Apache-2"
LIC_FILES_CHKSUM = "file://src/${GO_IMPORT}/LICENSE.txt;md5=00294979737b05a575493ff7b723f25c"

# PV = "7.9.1"
SRCREV = "${AUTOREV}"

FILESEXTRAPATHS_append = "${THISDIR}/elastic-beats:"

SRC_URI = " \
        git://${GO_IMPORT}.git \
        file://${GO_PACKAGE}.yml \
        "

RDEPENDS_${PN}-dev += "bash"

do_compile() {
    cd ${GO_PACKAGE}
    go build
    # This is needed to remove read-only files
    go clean -modcache
    rm -rf src/${GO_IMPORT}/pkg/mod
}

do_install() {
    create_exec_script

	install -d ${D}${bindir}/
	install -m 0755 ${WORKDIR}/${GO_PACKAGE} ${D}${bindir}

    install -d ${D}${datadir}/${GO_PACKAGE}
	install -m 0755 ${BEAT_FOLDER}/${GO_PACKAGE} ${D}${datadir}/${GO_PACKAGE}

    install -d ${D}${sysconfdir}/${GO_PACKAGE}
    install -m 0755 ${WORKDIR}/${GO_PACKAGE}.yml ${D}${sysconfdir}/${GO_PACKAGE}/${GO_PACKAGE}.yml

    install -d ${D}${localstatedir}/lib/${GO_PACKAGE}
    install -d ${D}${localstatedir}/log/${GO_PACKAGE}

}

create_exec_script() {
    if [ -f ${WORKDIR}/${GO_PACKAGE} ]; then
        rm ${WORKDIR}/${GO_PACKAGE}
    fi
    cat >> "${WORKDIR}/${GO_PACKAGE}" <<EOF
#!/usr/bin/env bash

# Script to run ${GO_PACKAGE} in foreground with the same path settings that
# the init script / systemd unit file would do.

exec ${datadir}/${GO_PACKAGE}/${GO_PACKAGE} \
  --path.home ${datadir}/${GO_PACKAGE} \
  --path.config ${sysconfdir}/${GO_PACKAGE} \
  --path.data ${localstatedir}/lib/${GO_PACKAGE} \
  --path.logs ${localstatedir}/log/${GO_PACKAGE} \
  "$@"

EOF
    chmod +x ${WORKDIR}/${GO_PACKAGE}
}

FILES_${PN} += " \
        ${datadir} \
        ${sysconfdir} \
"