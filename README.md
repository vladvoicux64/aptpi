# aptpd - a package tracker for apt

### Motivation

Because often apt gets dependency/recommended installation loops, autoremove fails to remove all the leftovers after
uninstalling a package.  
aptpd (apt private detective) aims to fix this, by rummaging through your apt `history.log` file and telling you exactly
what was installed and what must you uninstall in order to have a true removal of a package and it's
dependencies/recommended installations.

### Usage

To come...

### Abilities

Currently, aptpd can scan a `history.log` file and tell you what installations it found, including precise dates. It can
display the data to your console.
