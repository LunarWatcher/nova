## Core

* [ ] Dynamic linking
* [ ] CI
* [ ] Built-in modules
* [ ] Conanfile (for interface purposes; exporting headers through Conan)
* [ ] Testing
* [ ] API
* [ ] Packaging
* [ ] Challenges

## Dynamic linking
* [x] Linking core + flag resolution
* [ ] Find and load stuff on-demand
* [ ] Require a JSON manifest

## CI
* [x] Build
* [ ] Make the CI run tests

## Built-in modules
* [ ] HelpModule
* [ ] DashboardModule
    * [ ] System status
    * [ ] GitHub issue interface? API key might be the choke point here


## API
* [ ] Encryption
* [ ] Interaction with other programs
* [ ] Modules of modules
* [ ] Lua API
* [ ] On-demand module loading (will require a JSON file to be accompanied with each module for early resolution purposes)
* [ ] User config and API access to said config

## Testing
* [x] Set up testing
* [ ] Test dynamic loading and `NovaMain()`

Other testing is on a per-need basis, and doesn't need to be listed here. Test when necessary and useful.

## Packaging
* [ ] .deb
* [ ] .exe
* [ ] generic linux (x64, fuck 32 bit)
* [ ] Whatever macOS uses? Might also be a thing to backlog, can't test portability on this

## Challenges
* [ ] Conflict resolution: throw or force compat?
    * If force, what resolution system? Force number?
    * Drop invalid names with a warning?
