# GlassySnek

### Linux instructions:

1. make sure you have `python-config` executable in your path
    * `python-config` might not be symlinked on your computer, it is an executable that comes with a standard python installation
    * on mine (Arch linux), it was `/usr/bin/python3.6m-config` and I symlinked it to `/usr/bin/python-config`
2. install [poetry](https://python-poetry.org/): `curl -sSL https://raw.githubusercontent.com/python-poetry/poetry/master/get-poetry.py | python`
3. run `poetry install`
2. `cd` into `c` and run `sh go.sh`
3. cp `c/libglassysnek.*` to `/usr/local/lib`
4. in `src/lib_glassysnek.cr` change the ldflags to whatever the output of `python-config --ldflags` is
5. run `crystal src/GlassySnek.cr`

## Installation

1. Add the dependency to your `shard.yml`:

   ```yaml
   dependencies:
     GlassySnek:
       github: your-github-user/GlassySnek
   ```

2. Run `shards install`

## Usage

```crystal
require "GlassySnek"
```

TODO: Write usage instructions here

## Development

TODO: Write development instructions here

## Contributing

1. Fork it (<https://github.com/your-github-user/GlassySnek/fork>)
2. Create your feature branch (`git checkout -b my-new-feature`)
3. Commit your changes (`git commit -am 'Add some feature'`)
4. Push to the branch (`git push origin my-new-feature`)
5. Create a new Pull Request

## Contributors

- [Nick Franken](https://github.com/your-github-user) - creator and maintainer
