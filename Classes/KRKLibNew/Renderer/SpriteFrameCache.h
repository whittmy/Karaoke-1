#ifndef __SPRITE_SPRITE_FRAME_CACHE_H__
#define __SPRITE_SPRITE_FRAME_CACHE_H__

#include <set>
#include <string>
#include "Renderer/SpriteFrame.h"
#include "Base/Ref.h"
#include "Base/Value.h"
#include "Base/Map.h"


class Sprite;
class Texture2D;
class PolygonInfo;

/** @class SpriteFrameCache
 * @brief Singleton that handles the loading of the sprite frames.

 The SpriteFrameCache loads SpriteFrames from a .plist file.
 A SpriteFrame contains information about how to use a sprite
 located in a sprite sheet.
 
 The .plist file contains the following elements:

 - `frames`:
   Dictionary of sprites. Key is the sprite's name, value a dict containing the sprite frame data.
   A sprite frame consists of the following values:
    - `spriteOffset`:     difference vector between the original sprite's center and the center of the trimmed sprite
    - `spriteSize`:       size of the trimmed sprite
    - `spriteSourceSize`: size of the original sprite
    - `textureRect`:      the position of the sprite in the sprite sheet
    - `textureRotated`:   true if the sprite is rotated clockwise
   Optional values when using polygon outlines
    - `triangles`:        3 indices per triangle, pointing to vertices and verticesUV coordinates
    - `vertices`:         vertices in sprite coordinates, each vertex consists of a pair of x and y coordinates
    - `verticesUV`:       vertices in the sprite sheet, each vertex consists of a pair of x and y coordinates
 
 - `metadata`:
   Dictionary containing additional information about the sprite sheet:
     - `format`:          plist file format, currently 3
     - `size`:            size of the texture (optional)
     - `textureFileName`: name of the texture's image file
 
 Use one of the following tools to create the .plist file and sprite sheet:
 - [TexturePacker](https://www.codeandweb.com/texturepacker/cocos2d)
 - [Zwoptex](https://zwopple.com/zwoptex/)
 
 */
class SpriteFrameCache : public Ref
{
public:
    /** Returns the shared instance of the Sprite Frame cache.
     *
     * @return The instance of the Sprite Frame Cache.
     * @js NA
     */
    static SpriteFrameCache* getInstance();

    /** Destroys the cache. It releases all the Sprite Frames and the retained instance.
	 * @js NA
     */
    static void destroyInstance();

    /** Destructor.
     * @js NA
     * @lua NA
     */
    virtual ~SpriteFrameCache();
    
    /** Initialize method.
     *
     * @return if success return true.
     */
    bool init();

    /** Adds multiple Sprite Frames from a plist file.
     * A texture will be loaded automatically. The texture name will composed by replacing the .plist suffix with .png.
     * If you want to use another texture, you should use the addSpriteFramesWithFile(const std::string& plist, const std::string& textureFileName) method.
     * @js addSpriteFrames
     * @lua addSpriteFrames
     *
     * @param plist Plist file name.
     */
    void addSpriteFramesWithFile(const std::string& plist);

    /** Adds multiple Sprite Frames from a plist file. The texture will be associated with the created sprite frames.
     @since v0.99.5
     * @js addSpriteFrames
     * @lua addSpriteFrames
     *
     * @param plist Plist file name.
     * @param textureFileName Texture file name.
     */
    void addSpriteFramesWithFile(const std::string& plist, const std::string& textureFileName);

    /** Adds multiple Sprite Frames from a plist file. The texture will be associated with the created sprite frames. 
     * @js addSpriteFrames
     * @lua addSpriteFrames
     *
     * @param plist Plist file name.
     * @param texture Texture pointer.
     */
    void addSpriteFramesWithFile(const std::string&plist, Texture2D *texture);

    /** Adds multiple Sprite Frames from a plist file content. The texture will be associated with the created sprite frames. 
     * @js NA
     * @lua addSpriteFrames
     *
     * @param plist_content Plist file content string.
     * @param texture Texture pointer.
     */
    void addSpriteFramesWithFileContent(const std::string& plist_content, Texture2D *texture);

    /** Adds an sprite frame with a given name.
     If the name already exists, then the contents of the old name will be replaced with the new one.
     *
     * @param frame A certain sprite frame.
     * @param frameName The name of the sprite frame.
     */
    void addSpriteFrame(SpriteFrame *frame, const std::string& frameName);

    /** Check if multiple Sprite Frames from a plist file have been loaded.
    * @js NA
    * @lua NA
    *
    * @param plist Plist file name.
    * @return True if the file is loaded.
    */
    bool isSpriteFramesWithFileLoaded(const std::string& plist) const;

    /** Purges the dictionary of loaded sprite frames.
     * Call this method if you receive the "Memory Warning".
     * In the short term: it will free some resources preventing your app from being killed.
     * In the medium term: it will allocate more resources.
     * In the long term: it will be the same.
     */
    void removeSpriteFrames();

    /** Removes unused sprite frames.
     * Sprite Frames that have a retain count of 1 will be deleted.
     * It is convenient to call this method after when starting a new Scene.
	 * @js NA
     */
    void removeUnusedSpriteFrames();

    /** Deletes an sprite frame from the sprite frame cache. 
     *
     * @param name The name of the sprite frame that needs to removed.
     */
    void removeSpriteFrameByName(const std::string& name);

    /** Removes multiple Sprite Frames from a plist file.
    * Sprite Frames stored in this file will be removed.
    * It is convenient to call this method when a specific texture needs to be removed.
    * @since v0.99.5
    *
    * @param plist The name of the plist that needs to removed.
    */
    void removeSpriteFramesFromFile(const std::string& plist);

    /** Removes multiple Sprite Frames from a plist file content.
    * Sprite Frames stored in this file will be removed.
    * It is convenient to call this method when a specific texture needs to be removed.
    *
    * @param plist_content The string of the plist content that needs to removed.
    * @js NA
    */
    void removeSpriteFramesFromFileContent(const std::string& plist_content);

    /** Removes all Sprite Frames associated with the specified textures.
     * It is convenient to call this method when a specific texture needs to be removed.
     * @since v0.995.
     *
     * @param texture The texture that needs to removed.
     */
    void removeSpriteFramesFromTexture(Texture2D* texture);

    /** Returns an Sprite Frame that was previously added.
     If the name is not found it will return nil.
     You should retain the returned copy if you are going to use it.
     * @js getSpriteFrame
     * @lua getSpriteFrame
     *
     * @param name A certain sprite frame name.
     * @return The sprite frame.
     */
    SpriteFrame* getSpriteFrameByName(const std::string& name);

    bool reloadTexture(const std::string& plist);

protected:
    // MARMALADE: Made this protected not private, as deriving from this class is pretty useful
    SpriteFrameCache(){}

    /*Adds multiple Sprite Frames with a dictionary. The texture will be associated with the created sprite frames.
     */
    void addSpriteFramesWithDictionary(ValueMap& dictionary, Texture2D *texture);

    /** Removes multiple Sprite Frames from Dictionary.
    * @since v0.99.5
    */
    void removeSpriteFramesFromDictionary(ValueMap& dictionary);

    /** Parses list of space-separated integers */
    void parseIntegerList(const std::string &string, std::vector<int> &res);
    
    /** Configures PolygonInfo class with the passed sizes + triangles */
    void initializePolygonInfo(const Size &textureSize,
                               const Size &spriteSize,
                               const std::vector<int> &vertices,
                               const std::vector<int> &verticesUV,
                               const std::vector<int> &triangleIndices,
                               PolygonInfo &polygonInfo);

    void reloadSpriteFramesWithDictionary(ValueMap& dictionary, Texture2D *texture);

    Map<std::string, SpriteFrame*> _spriteFrames;
    ValueMap _spriteFramesAliases;
    std::set<std::string>*  _loadedFileNames;
};

#endif // __SPRITE_SPRITE_FRAME_CACHE_H__
