/**
 *  This file is part of SoftGREd
 *
 *    SoftGREd is free software: you can redistribute it and/or modify it under the terms
 *  of the GNU Lesse General Public License as published by the Free Software Foundation, either
 *  version 3 of the License, or (at your option) any later version.
 *
 *  SoftGREd is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 *  without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *  See the GNU Lesse General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesse General Public License
 *  along with SoftGREd.
 *  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Copyright (C) 2014, Jorge Pereira <jpereiran@gmail.com>
 */

#ifndef SOFTGRED_CONFIG_H_
#define SOFTGRED_CONFIG_H_

#include "general.h"
#include "config.h"

#define SOFTGRED_MAX_ATTACH         10
#define SOFTGRED_MAX_IFACE          IFNAMSIZ
#define SOFTGRED_MAX_SLOTS          4096
#define SOFTGRED_TUN_PREFIX         "sgre" 
#define SOFTGRED_TUN_PREFIX_MAX     10
#define SOFTGRED_TUN_MTU            1462

struct tunnel_bridge {
    const char *ifname;
    uint16_t vlan_id;
};

struct tunnel_context_priv {
    char ifname_ip[SOFTGRED_MAX_IFACE+1];
    struct sockaddr_in ifname_saddr;
};

struct softgred_config_debug_env {
    const char *var;
    bool *flag;
};

#define is_debug(__peace)             (softgred_config_get_ref()->debug_env.__peace == true)
#define if_debug(__peace, __doit)     if(is_debug(__peace)) { __doit; }

enum data_type {
    T_STRING,
    T_BOOL,
    T_UINT32, 
    T_INT32
};

static const char *
data_T_get_name (enum data_type type)
{
    switch (type)
    {
        case T_STRING: return "string";
        case T_BOOL: return "boolean";
        case T_INT32: return "int32_t";
        case T_UINT32: return "uint32_t";
        default: return "unknown";
    }
}

struct config_file {
    const char *group_name; /* group name */
    const char *key;        /* config key name */
    bool is_necessary;      /* is necessary? */
    enum data_type type;    /* expected type of value */
    void **ptr;             /* where will be save */
};

struct softgred_config {
    bool is_foreground;     /* --foreground */
    char *ifname;           /* --iface */
    char *tunnel_prefix;    /* --tunnel-prefix */
    char *pid_file;         /* --pid-file */

    int32_t debug_mode;     /* --debug */
    bool debug_xmode;       /* --xdebug */
    bool print_time;        /* --print-time */

    bool bridge_force;
    char *bridge_map;
    struct tunnel_bridge bridge[SOFTGRED_MAX_ATTACH];
    uint8_t bridge_slot;

    struct {
        char *bind_in;
        uint16_t port;
        uint32_t max_listen;
    } service;

    int debug_level;

    struct {
        bool payload;        /* getenv("SOFTGRED_DEBUG_PAYLOAD") */
        bool cmd;            /* getenv("SOFTGRED_DEBUG_CMD") */
        bool provision;      /* getenv("SOFTGRED_DEBUG_PROVISION") */
        bool service;        /* getenv("SOFTGRED_DEBUG_SERVICE") */
    } debug_env; /* set by softgred_config_load_envs() */

    struct tunnel_context_priv priv;
    struct rtnl_handle rth;
    hash_table_t *table;
    time_t started_time;
    struct utsname uts;
};

struct softgred_config *softgred_config_get_ref();

int softgred_config_init();

int softgred_config_end();

void softgred_config_load_envs();

int softgred_config_load_config_file(const char *config_file);

int softgred_config_load_cli(int argc, 
                             char *argv[]);

int softgred_config_load_iface(const char *ifname,
                               struct softgred_config *cfg);

int softgred_config_load_attach(const char *arg,
                                struct softgred_config *cfg);

int softgred_config_create_pid_file(int pid);

void softgred_print_version();

void softgred_print_usage(char *argv[]);

#endif /*SOFTGRED_CONFIG_H_*/

