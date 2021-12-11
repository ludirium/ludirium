Sample init scripts and service configuration for ludiriumd
==========================================================

Sample scripts and configuration files for systemd, Upstart and OpenRC
can be found in the contrib/init folder.

    contrib/init/ludiriumd.service:    systemd service unit configuration
    contrib/init/ludiriumd.openrc:     OpenRC compatible SysV style init script
    contrib/init/ludiriumd.openrcconf: OpenRC conf.d file
    contrib/init/ludiriumd.conf:       Upstart service configuration file
    contrib/init/ludiriumd.init:       CentOS compatible SysV style init script

Service User
---------------------------------

All three Linux startup configurations assume the existence of a "ludirium" user
and group.  They must be created before attempting to use these scripts.
The macOS configuration assumes ludiriumd will be set up for the current user.

Configuration
---------------------------------

Running ludiriumd as a daemon does not require any manual configuration. You may
set the `rpcauth` setting in the `ludirium.conf` configuration file to override
the default behaviour of using a special cookie for authentication.

This password does not have to be remembered or typed as it is mostly used
as a fixed token that ludiriumd and client programs read from the configuration
file, however it is recommended that a strong and secure password be used
as this password is security critical to securing the wallet should the
wallet be enabled.

If ludiriumd is run with the "-server" flag (set by default), and no rpcpassword is set,
it will use a special cookie file for authentication. The cookie is generated with random
content when the daemon starts, and deleted when it exits. Read access to this file
controls who can access it through RPC.

By default the cookie is stored in the data directory, but it's location can be overridden
with the option '-rpccookiefile'.

This allows for running ludiriumd without having to do any manual configuration.

`conf`, `pid`, and `wallet` accept relative paths which are interpreted as
relative to the data directory. `wallet` *only* supports relative paths.

For an example configuration file that describes the configuration settings,
see `share/examples/ludirium.conf`.

Paths
---------------------------------

### Linux

All three configurations assume several paths that might need to be adjusted.

    Binary:              /usr/bin/ludiriumd
    Configuration file:  /etc/ludirium/ludirium.conf
    Data directory:      /var/lib/ludiriumd
    PID file:            /var/run/ludiriumd/ludiriumd.pid (OpenRC and Upstart) or
                         /run/ludiriumd/ludiriumd.pid (systemd)
    Lock file:           /var/lock/subsys/ludiriumd (CentOS)

The PID directory (if applicable) and data directory should both be owned by the
ludirium user and group. It is advised for security reasons to make the
configuration file and data directory only readable by the ludirium user and
group. Access to ludirium-cli and other ludiriumd rpc clients can then be
controlled by group membership.

NOTE: When using the systemd .service file, the creation of the aforementioned
directories and the setting of their permissions is automatically handled by
systemd. Directories are given a permission of 710, giving the ludirium group
access to files under it _if_ the files themselves give permission to the
ludirium group to do so (e.g. when `-sysperms` is specified). This does not allow
for the listing of files under the directory.

NOTE: It is not currently possible to override `datadir` in
`/etc/ludirium/ludirium.conf` with the current systemd, OpenRC, and Upstart init
files out-of-the-box. This is because the command line options specified in the
init files take precedence over the configurations in
`/etc/ludirium/ludirium.conf`. However, some init systems have their own
configuration mechanisms that would allow for overriding the command line
options specified in the init files (e.g. setting `LUDIRIUMD_DATADIR` for
OpenRC).

### macOS

    Binary:              /usr/local/bin/ludiriumd
    Configuration file:  ~/Library/Application Support/Ludirium/ludirium.conf
    Data directory:      ~/Library/Application Support/Ludirium
    Lock file:           ~/Library/Application Support/Ludirium/.lock

Installing Service Configuration
-----------------------------------

### systemd

Installing this .service file consists of just copying it to
/usr/lib/systemd/system directory, followed by the command
`systemctl daemon-reload` in order to update running systemd configuration.

To test, run `systemctl start ludiriumd` and to enable for system startup run
`systemctl enable ludiriumd`

NOTE: When installing for systemd in Debian/Ubuntu the .service file needs to be copied to the /lib/systemd/system directory instead.

### OpenRC

Rename ludiriumd.openrc to ludiriumd and drop it in /etc/init.d.  Double
check ownership and permissions and make it executable.  Test it with
`/etc/init.d/ludiriumd start` and configure it to run on startup with
`rc-update add ludiriumd`

### Upstart (for Debian/Ubuntu based distributions)

Upstart is the default init system for Debian/Ubuntu versions older than 15.04. If you are using version 15.04 or newer and haven't manually configured upstart you should follow the systemd instructions instead.

Drop ludiriumd.conf in /etc/init.  Test by running `service ludiriumd start`
it will automatically start on reboot.

NOTE: This script is incompatible with CentOS 5 and Amazon Linux 2014 as they
use old versions of Upstart and do not supply the start-stop-daemon utility.

### CentOS

Copy ludiriumd.init to /etc/init.d/ludiriumd. Test by running `service ludiriumd start`.

Using this script, you can adjust the path and flags to the ludiriumd program by
setting the LUDIRIUMD and FLAGS environment variables in the file
/etc/sysconfig/ludiriumd. You can also use the DAEMONOPTS environment variable here.

### macOS

Copy org.ludirium.ludiriumd.plist into ~/Library/LaunchAgents. Load the launch agent by
running `launchctl load ~/Library/LaunchAgents/org.ludirium.ludiriumd.plist`.

This Launch Agent will cause ludiriumd to start whenever the user logs in.

NOTE: This approach is intended for those wanting to run ludiriumd as the current user.
You will need to modify org.ludirium.ludiriumd.plist if you intend to use it as a
Launch Daemon with a dedicated ludirium user.

Auto-respawn
-----------------------------------

Auto respawning is currently only configured for Upstart and systemd.
Reasonable defaults have been chosen but YMMV.
