#ifndef GameEngine_ObjParser_H
#define GameEngine_ObjParser_H

#include "ISceneParser.h"

namespace GameEngine
{
	class Scene;
    class ObjParser : public ISceneParser
    {
    public:
        virtual std::unique_ptr<Scene> Parse(const std::string &buf);

        std::unique_ptr<Scene> LoadObj(std::istream &inStream);

		inline bool isSpace(const char c) { return (c == ' ') || (c == '\t'); }

		inline void parseFloat3(float &x, float &y, float &z,
			const char *&token)
		{
			x = parseFloat(token);
			y = parseFloat(token);
			z = parseFloat(token);
		}
		inline void parseFloat2(float &x, float &y, const char *&token)
		{
			x = parseFloat(token);
			y = parseFloat(token);
		}
		inline float parseFloat(const char *&token)
		{
			token += strspn(token, " \t");
			const char *end = token + strcspn(token, " \t\r");
			double val = 0.0;
			tryParseDouble(token, end, &val);
			float f = static_cast<float>(val);
			token = end;
			return f;
		}

		bool tryParseDouble(const char *s, const char *s_end, double *result);
    };

} // namespace GameEngine

#endif