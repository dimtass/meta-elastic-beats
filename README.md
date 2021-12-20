meta-elastic-beats
----

This is a recipe meta layer for Yocto that builds the official elastic beats
found [here](https://www.elastic.co/beats/). Elastic beats are lightweight
data clients that can send data to various tools of the Elastic Stack, like
[Elasticsearch](https://www.elastic.co/elasticsearch/),
[Kibana](elastic.co/kibana) and 
[Logstash](https://www.elastic.co/logstash).

> Note: If you're interested on how to use beats in embedded and Yocto or how
to create your own beats then read these posts in my blog
[post 1](https://www.stupid-projects.com/using-elastic-stack-elk-on-embedded-part-1/),
[post 2](https://www.stupid-projects.com/using-elastic-stack-elk-on-embedded-part-2/).

## Supported beats
The supported beats currently are:

* [auditbeat](https://www.elastic.co/beats/auditbeat)
* [filebeat](https://www.elastic.co/beats/filebeat)
* [heartbeat](https://www.elastic.co/beats/heartbeat)
* [journalbeat](https://www.elastic.co/guide/en/beats/journalbeat/current/journalbeat-overview.html)
* [metricbeat](https://www.elastic.co/beats/metricbeat)
* [packetbeat](https://www.elastic.co/beats/packetbeat)

## Supported versions
The master repo recipes point always to the latest master `SRCREV = "${AUTOREV}"`,
but there are tags in the repo for specific and tested versions.
The supported versions (and repo tags) are:

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

The configuration yaml files are the default ones. You need to override them
with a custom recipe and use your own for your specific usage. The configuration
Yaml files are located in `meta-elastic-beats/recipes-devops/elastic-beats/elastic-beats`.

## Known issues
The golang build changes the files in pkg/mod in to read only. This means that
bitbake is not able to delete those files if the build fails and you need to
delete the folder manually. Normally this is handled in `meta-elastic-beats/recipes-devops/elastic-beats/elastic-beats.inc`
with the `go clean -modcache` comamnd. 

## Maintainer
Dimitris Tassopoulos <dimtass@gmail.com>
