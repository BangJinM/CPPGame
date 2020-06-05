#include "ObjParser.h"
#include <fstream>
#include <sstream>
#include <string>
#include <cassert>
#include <cstdint>
#include <vector>
#include "Scene.h"

namespace GameEngine
{

	bool ObjParser::tryParseDouble(const char *s, const char *s_end, double *result)
	{
		if (s >= s_end)
		{
			return false;
		}

		double mantissa = 0.0;

		int exponent = 0;

		char sign = '+';
		char exp_sign = '+';
		char const *curr = s;

		int read = 0;
		bool end_not_reached = false;

		if (*curr == '+' || *curr == '-')
		{
			sign = *curr;
			curr++;
		}
		else if (isdigit(*curr))
		{ /* Pass through. */
		}
		else
		{
			goto fail;
		}

		// Read the integer part.
		while ((end_not_reached = (curr != s_end)) && isdigit(*curr))
		{
			mantissa *= 10;
			mantissa += static_cast<int>(*curr - 0x30);
			curr++;
			read++;
		}

		// We must make sure we actually got something.
		if (read == 0)
			goto fail;
		// We allow numbers of form "#", "###" etc.
		if (!end_not_reached)
			goto assemble;

		// Read the decimal part.
		if (*curr == '.')
		{
			curr++;
			read = 1;
			while ((end_not_reached = (curr != s_end)) && isdigit(*curr))
			{
				// NOTE: Don't use powf here, it will absolutely murder precision.
				mantissa += static_cast<int>(*curr - 0x30) * pow(10.0, -read);
				read++;
				curr++;
			}
		}
		else if (*curr == 'e' || *curr == 'E')
		{
		}
		else
		{
			goto assemble;
		}

		if (!end_not_reached)
			goto assemble;

		// Read the exponent part.
		if (*curr == 'e' || *curr == 'E')
		{
			curr++;
			// Figure out if a sign is present and if it is.
			if ((end_not_reached = (curr != s_end)) && (*curr == '+' || *curr == '-'))
			{
				exp_sign = *curr;
				curr++;
			}
			else if (isdigit(*curr))
			{ /* Pass through. */
			}
			else
			{
				// Empty E is not allowed.
				goto fail;
			}

			read = 0;
			while ((end_not_reached = (curr != s_end)) && isdigit(*curr))
			{
				exponent *= 10;
				exponent += static_cast<int>(*curr - 0x30);
				curr++;
				read++;
			}
			exponent *= (exp_sign == '+' ? 1 : -1);
			if (read == 0)
				goto fail;
		}

	assemble:
		*result = (sign == '+' ? 1 : -1) * ldexp(mantissa * pow(5.0, exponent), exponent);
		return true;
	fail:
		return false;
	}

	std::unique_ptr<Scene> ObjParser::Parse(const std::string &buf)
	{
		std::istringstream inStream(buf.c_str());
		LoadObj(inStream);
		return std::unique_ptr<Scene>();
	}

	std::unique_ptr<Scene> ObjParser::LoadObj(std::istream &inStream)
	{
		std::vector<float> vertices;
		std::vector<float> vertexNormals;
		std::vector<float> textureVertices;
		std::vector<int> verticeIndex;	   // 顶点索引
		std::vector<int> texturCoordIndex; // 顶点索引
		std::vector<int> normalIndex;	   // 顶点索引

		int maxchars = 8192;			 // Alloc enough size.
		std::vector<char> buf(maxchars); // Alloc enough size.
		while (inStream.peek() != -1)
		{
			inStream.getline(&buf[0], maxchars);
			std::string linebuf(&buf[0]);

			// Trim newline '\r\n' or '\n'
			while (linebuf.size() > 0 && (linebuf[linebuf.size() - 1] == '\n' || linebuf[linebuf.size() - 1] == '\r'))
			{
				linebuf.erase(linebuf.size() - 1);
			}

			// Skip if empty line.
			if (linebuf.empty())
			{
				continue;
			}

			// Skip leading space.
			const char *token = linebuf.c_str();
			token += strspn(token, " \t");

			assert(token);
			if (token[0] == '\0')
				continue; // empty line

			if (token[0] == '#')
				continue; // comment line

			// vertex
			if (token[0] == 'v' && isSpace((token[1])))
			{
				token += 2;
				float x, y, z;
				parseFloat3(x, y, z, token);
				vertices.push_back(x);
				vertices.push_back(y);
				vertices.push_back(z);
				continue;
			}

			// normal
			if (token[0] == 'v' && token[1] == 'n' && isSpace((token[2])))
			{
				token += 3;
				float x, y, z;
				parseFloat3(x, y, z, token);
				vertexNormals.push_back(x);
				vertexNormals.push_back(y);
				vertexNormals.push_back(z);
				continue;
			}

			// texcoord
			if (token[0] == 'v' && token[1] == 't' && isSpace((token[2])))
			{
				token += 3;
				float x, y;
				parseFloat2(x, y, token);
				textureVertices.push_back(x);
				textureVertices.push_back(y);
				continue;
			}

			// face
			if (token[0] == 'f' && isSpace((token[1])))
			{
				token += 2;
				token += strspn(token, " \t");

				auto first = static_cast<int>(vertices.size() / 3);
				auto second = static_cast<int>(vertexNormals.size() / 3);
				auto third = static_cast<int>(textureVertices.size() / 2);
				while (!isNewLine(token[0]))
				{
					int v_idx,vn_idx,vt_idx;
					parseTriple(token, first, second, third, verticeIndex, normalIndex, texturCoordIndex);
					size_t n = strspn(token, " \t\r");
					token += n;
				}

				continue;
			}
		}
		return std::unique_ptr<Scene>();
	}
	void ObjParser::parseTriple(const char *& token, int vsize, int vnsize, int vtsize, std::vector<int> & verticeIndex, std::vector<int>&  normalIndex, std::vector<int>&  texturCoordIndex)
	{
		int v_idx, vn_idx, vt_idx;
		v_idx = fixIndex(atoi(token), vsize);
		token += strcspn(token, "/ \t\r");
		if (token[0] != '/')
		{
			verticeIndex.push_back(v_idx);
			return;
		}
		token++;

		// i//k
		if (token[0] == '/')
		{
			token++;
			vn_idx = fixIndex(atoi(token), vnsize);
			token += strcspn(token, "/ \t\r");
			verticeIndex.push_back(v_idx);
			normalIndex.push_back(vn_idx);
			return;
		}

		// i/j/k or i/j
		vt_idx = fixIndex(atoi(token), vtsize);
		token += strcspn(token, "/ \t\r");
		if (token[0] != '/')
		{
			verticeIndex.push_back(v_idx);
			texturCoordIndex.push_back(vt_idx);
			return;
		}

		// i/j/k
		token++; // skip '/'
		vn_idx = fixIndex(atoi(token), vnsize);
		token += strcspn(token, "/ \t\r");
		verticeIndex.push_back(v_idx);
		normalIndex.push_back(vn_idx);
		texturCoordIndex.push_back(vt_idx);
		return;
	}

} // namespace GameEngine
