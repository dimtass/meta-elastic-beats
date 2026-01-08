meta-elastic-beats
----

This is a recipe meta layer for Yocto that builds the official elastic beats
found [here](https://www.elastic.co/beats/). Elastic beats are lightweight
data clients that can send data to various tools of the Elastic Stack, like
[Elasticsearch](https://www.elastic.co/elasticsearch/),
[Kibana](elastic.co/kibana) and 
[Logstash](https://www.elastic.co/logstash).

## Introduction

Beats can be installed in custom linux images using Yocto. It is preferred to run beats as systemd services, this implementation does exactly that. After the image is built, beats will be installed as systemd services and can be used to monitor different aspects of the systems. This project is primarily focused on embedded systems but can be used for any custom linux.


## Supported beats
The supported beats currently are:

* [auditbeat](https://www.elastic.co/beats/auditbeat)
* [filebeat](https://www.elastic.co/beats/filebeat)
* [heartbeat](https://www.elastic.co/beats/heartbeat)
* [metricbeat](https://www.elastic.co/beats/metricbeat)
* [packetbeat](https://www.elastic.co/beats/packetbeat)

## Supported versions

* v8.14.3

## Adding systemd support

It is very important that the distribution being built supports systemd. To add systemd support, in build/local.conf following lines can be added:

```sh
CONF_VERSION = "2"

DISTRO_FEATURES:append = " systemd usrmerge"
DISTRO_FEATURES_BACKFILL_CONSIDERED += "sysvinit"
VIRTUAL-RUNTIME_init_manager = "systemd"
VIRTUAL-RUNTIME_initscripts = ""
```

## Adding the meta-elastic-beats layer to your build

To add the layer to your build :

```sh
bitbake-layers add-layer meta-elastic-beats
```

Or just simply add the layer manually to your `bblayers.conf` file.

## Adding beats to your image
To add a beat in your image then add one of the following recipes to your
`IMAGE_INSTALL`:

```sh
elastic-beats-auditbeat
elastic-beats-filebeat
elastic-beats-heartbeat
elastic-beats-metricbeat
elastic-beats-packetbeat
```

For example:

```sh
IMAGE_INSTALL += "elastic-beats-journalbeat elastic-beats-metricbeat"
```

The configuration yaml files are the default ones. You need to override them
with a custom recipe and use your own for your specific usage. The configuration
Yaml files are located in `meta-elastic-beats/recipes-devops/elastic-beats/elastic-beats`.

## Maintainer
Dimitris Tassopoulos <dimtass@gmail.com>
