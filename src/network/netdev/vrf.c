/* SPDX-License-Identifier: LGPL-2.1-or-later */

#include <net/if.h>

#include "vrf.h"

static int netdev_vrf_fill_message_create(NetDev *netdev, Link *link, sd_netlink_message *m) {
        Vrf *v;
        int r;

        assert(netdev);
        assert(!link);
        assert(m);

        v = VRF(netdev);

        assert(v);

        r = sd_netlink_message_append_u32(m, IFLA_VRF_TABLE, v->table);
        if (r < 0)
                return log_netdev_error_errno(netdev, r, "Could not append IFLA_VRF_TABLE attribute: %m");

        return r;
}

const NetDevVTable vrf_vtable = {
        .object_size = sizeof(Vrf),
        .sections = NETDEV_COMMON_SECTIONS "VRF\0",
        .fill_message_create = netdev_vrf_fill_message_create,
        .create_type = NETDEV_CREATE_MASTER,
        .generate_mac = true,
};
