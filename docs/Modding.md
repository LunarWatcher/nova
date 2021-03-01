# Modding Nova

Nova is meant to be possible to extend in a number of ways. Aside offering plain JSON configuration for times where an entire module is overkill, she supports dynamic loading of libraries to take advantage of the entirety of C++ for extending Nova.

This is largely to make Nova not just a terminal utility, but an extensible API to help with various things.

One example of this is the built-in encrypted notepad module [Note: not implemented at the time of writing; docs partially written before actually writing code]. There's already dozens of encrypted notetaking plugins, but Nova's module lets you write notes in any app you'd like (as long as termination of the app can be monitored by Nova), and Nova will handle encryption and decryption. This also means you can use whatever format you want, with whatever editor plugins you want.

This is part of the flexibility intended behind the API; Nova is meant to let you do what you want easily -- with a base API included, and things such as input processing handled for you, Nova is meant to make automation or even making entire programs substantially easier.

Wanna add a dashboard? Hook up some C++ code and ncurses (or your favorite terminal UI library, or write it from scratch), and code whatever you want. Input processing and certain interfaces are handled.

Not everything requires you to make an entire module, or be familiar with C++, though. With a bit of JSON configuration, you can configure modules (assuming the module supports it), or just do generic configuration in using a combination of shell commands, Nova templates, and Nova commands/modules.

When the technical details are in place, this document will be expanded with documentation and examples on these things rather than just containing a tiny marketing speech about the future.

## Includes

Nova, being powered by SCons and Conan, exposes an SConscript for use as a submodule (although some modules may be contained as Git submodules, but still have the submodules use Nova as a direct dependency).

Tiny possible recursive trap aside, to implement modules by using the Nova API, your dynamic library needs to add the `include` folder to its search path, as well as include various conan dependencies. The SConscript briefly mentioned earlier does this for you (note: not at the time of writing, will be implemented later). If you choose to use SCons, this is an easy setup option. Call `SConscript` against the file, and it'll take care of the rest.

**Note:** While only SCons is supported at the moment, pull requests adding submodule equivalents for other buildscripts are welcome. Note that buildscript files for building Nova itself are going to continue using SCons, because there's no point in fracturing the primary build system. Module interfaces need to support lots of options, but the options for building Nova itself shouldn't.

TODO: determine whether or not several modules potentially linking against Conan dependencies causes problems. (Disregard Windows frameworks, MSVC users should figure that out on their own.)

## Making extensions

Nova extensions are primarily based on `Module`s. You create your own classes extending `Module`, and register it in the `ModuleTree`.

### `NovaMain()`

`NovaMain()` is a special function for dynamic libraries. This function is kinda the entry point to your dynamic library, The motivation behind this is that only Windows has DllMain (see [this](https://stackoverflow.com/a/12463991/6296561)), so for true portability, Nova calls a custom function to make sure everything is intialized.

Due to dynamic library mechanics, this is the easiest way to initialize everything.

### `ModuleTree` and registering extensions

Just having stuff added to a dynamic library isn't enough

### The manifest

Each module is required to have a manifest. The manifest is written in JSON (largely because it's flexible and there's tools to parse it, which means I can implement generic parsing in a way that doesn't prevent modding that involves the manifest).

The general syntax is:
```json
{
    "dyname": "examplelib",
    "modules": [
        {
            "load": "ondemand|alwaysload",
            "moduleCommand": {
                "name": "domagic",
                "aliases": ["optional"]
            },
            "trigger": "othercommand"
        }
    ]
}
```

#### Top-level reference

| Key               | Type       | Meaning                                 | If optional, default value |
| ----------------- | ---------- | --------------------------------------- | -------------------------- |
| `dyname`          | string     | Shared library name (without extension) |                            |
| `modules`         | list       | List of module objects                  |                            |

#### Module reference:

| Key               | Type       | Meaning                                 | If optional, default value | Allowed values       |
| ----------------- | ---------- | --------------------------------------- | -------------------------- | -------------------- |
| `load`            | string     | When to load the library                | ondemand                   | ondemand, alwaysload |
| `moduleCommand`   | object     | Defines execution details               |                            |                      |
| `trigger`         | string     | Used if the module is a submodule. The variable is used to determine what command structure. If this is an empty string, it'll assume it's a top-level command. Otherwise, it'll define a submodule. | "" | |

An additional note on triggers:

#### Module command reference:

| Key               | Type       | Meaning                                 | If optional, default value |
| ----------------- | ---------- | --------------------------------------- | -------------------------- |
| `name`            | string     | What name is used to execute the module |                            |
| `aliases`         | list       | Alternative names for the module        | []                         |
