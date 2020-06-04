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
		std::vector<float> v;
		std::vector<float> vn;
		std::vector<float> vt;

		int maxchars = 8192;			 // Alloc enough size.
		std::vector<char> buf(maxchars); // Alloc enough size.
		while (inStream.peek() != -1)
		{
			inStream.getline(&buf[0], maxchars);
			std::string linebuf(&buf[0]);

			// Trim newline '\r\n' or '\n'
			if (linebuf.size() > 0)
			{
				if (linebuf[linebuf.size() - 1] == '\n')
					linebuf.erase(linebuf.size() - 1);
			}
			if (linebuf.size() > 0)
			{
				if (linebuf[linebuf.size() - 1] == '\r')
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
				
			if (token[0] == 'g')
				printf(linebuf.data());// comment line
			// vertex
			if (token[0] == 'v' && isSpace((token[1])))
			{
				token += 2;
				float x, y, z;
				parseFloat3(x, y, z, token);
				v.push_back(x);
				v.push_back(y);
				v.push_back(z);
				continue;
			}
			printf(linebuf.data());
			printf("\n");
		}
		return std::unique_ptr<Scene>();
	}

} // namespace GameEngine
