class Options
{
private:
    bool *preserveAspectRatio = 0;
    bool *interactive = 0;
    int *height = 0;
    int *width = 0;

    enum Type {IMAGE, TEXT, DOCUMENT, AUDIO, VIDEO};
    Type *type = 0;
    
    enum ColourSpace {BASH8, BASH24, HTML};
    ColourSpace *colourSpace = 0;
    
    enum OutputMode {BW, COLOUR};
    OutputMode *outputMode = 0;
};