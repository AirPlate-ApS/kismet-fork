https://www.kismetwireless.net

The Kismet docs can be most easily found and read at [the Kismet website](https://www.kismetwireless.net/docs/readme/intro/kismet/)


The docs repository is at:

```bash
$ git clone https://www.kismetwireless.net/git/kismet-docs.git
```

and mirrored on Github at:

```bash
$ git clone https://www.github.com/kismetwireless/kismet-docs
```

## Modifications made (searchable using the 'ADDED'-keyword):

* ./capture_antsdr_droneid/capture_antsdr_droneid.c

Exposing rssi, device_type_8, speed_e, speed_n and speed_u that currently is stored on the ant_droneid-struct, but not exposed over the Kismet API.

When calling the cf_send_json-function, it now includes a struct of cf_params_signal-type instead of NULL, which holds these fields, although the field names of the struct doesn't match what is being stored.

* ./capture_framework.c

Kismet doesn't always deem it neccessary to expose parameters about the signal, instead it depends on the metadata returned from the packet to decide its origin (i.e. which datasource captured it) and more.

The antsdr-plugin doesn't provide the right metadata to expose the signal parameters, as such

```c
if (meta == NULL) {
  return 0;
}
```

is commented out.

* ./devicetracker_component.cc

Depending on the signal-/packet-type, Kismet appends certain fields about the signal to the payload being sent to the API; if the signal unit is dbm, it exposes the parameters in dbm units, vice versa if the signal unit is rssi.

Neither is true for the antsdr-plugin, as such the fields are appended independently of the signal unit.
