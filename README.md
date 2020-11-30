# fw_img_payload
This a payload to reboot into a fw.img from the root of your sd card. Based on [cfw_booter](https://github.com/dimok789/cfw_booter)

## Usage
Place the `fw.img` in the root of your sd card (`sd:/fw.img`) and run a payload.elf loader (for example using the [browser exploit](https://github.com/wiiu-env/JsTypeHax)).

## Building

For building you just need [wut](https://github.com/devkitPro/wut/) installed, then use the `make` command.


```
# Build docker image (only needed once)
docker build . -t fw_img_payload-builder

# make 
docker run -it --rm -v ${PWD}:/project fw_img_payload-builder make

# make clean
docker run -it --rm -v ${PWD}:/project fw_img_payload-builder make clean
```

## Credits
dimok
Maschell