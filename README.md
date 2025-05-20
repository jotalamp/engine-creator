# Engine Creator

Tool for creating engines for AngeTheGreat's [Engine Simulator](https://github.com/ange-yaghi/engine-sim)

Can change values and units of template_engine.mr and save to file

Template engine is original engine from engine simulator: [engine file](https://github.com/ange-yaghi/engine-sim/blob/master/assets/engines/audi/i5.mr)

```
gh repo clone jotalamp/engine-creator -- --recurse-submodules 
mkdir build
cd build
cmake .. && make && make install && ../bin/test && ../bin/engine-creator
```

![Screenshot of EngineCreator app running](images/engine-creator-01.png)