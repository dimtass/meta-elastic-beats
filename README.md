meta-elastic-beats
----

This is a recipe meta layer for Yocto that builds the official elastic beats
found [here](https://www.elastic.co/beats/). Elastic beats are lightweight
data clients that can send data to various tools of the Elastic Stack, like
[Elasticsearch](https://www.elastic.co/elasticsearch/),
[Kibana](elastic.co/kibana) and 
[Logstash](https://www.elastic.co/logstash).

## Supported beats
The supported beats currently are:

* [auditbeat](https://www.elastic.co/beats/auditbeat)
* [filebeat](https://www.elastic.co/beats/filebeat)
* [heartbeat](https://www.elastic.co/beats/heartbeat)
* [journalbeat
* [metricbeat](https://www.elastic.co/beats/metricbeat)
* [packetbeat](https://www.elastic.co/beats/packetbeat)

## Supported versions
The supported versions are:

* v7.9.0

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
elastic-beats-journalbeat
elastic-beats-metricbeat
elastic-beats-packetbeat
```

For example:

```sh
IMAGE_INSTALL += "elastic-beats-journalbeat elastic-beats-metricbeat"
```

## Maintainer
Dimitris Tassopoulos <dimtass@gmail.com>