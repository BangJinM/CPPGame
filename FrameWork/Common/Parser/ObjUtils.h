//
// Copyright 2012-2015, Syoyo Fujita.
//
// Licensed under 2-clause BSD license.
//
//https://github.com/syoyo/tinyobjloader
#ifndef _GameEngine_Common_Scene_OBJ_LOADER_Utils_H
#define _GameEngine_Common_Scene_OBJ_LOADER_Utils_H

#include <cstdlib>
#include <cstring>
#include <cassert>
#include <cmath>
#include <cstddef>

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>

#include "AssetLoader.h"
#include "ObjLoader.h"

namespace GameEngine
{
    struct vertex_index
    {
        int v_idx, vt_idx, vn_idx;
        vertex_index(){};
        vertex_index(int idx) : v_idx(idx), vt_idx(idx), vn_idx(idx){};
        vertex_index(int vidx, int vtidx, int vnidx)
            : v_idx(vidx), vt_idx(vtidx), vn_idx(vnidx){};
    };

    static inline bool isSpace(const char c) { return (c == ' ') || (c == '\t'); }

    static inline bool isNewLine(const char c)
    {
        return (c == '\r') || (c == '\n') || (c == '\0');
    }

    // Make index zero-base, and also support relative index.
    static inline int fixIndex(int idx, int n)
    {
        if (idx > 0)
            return idx - 1;
        if (idx == 0)
            return 0;
        return n + idx; // negative value = relative
    }

    static inline std::string parseString(const char *&token)
    {
        std::string s;
        token += strspn(token, " \t");
        size_t e = strcspn(token, " \t\r");
        s = std::string(token, &token[e]);
        token += e;
        return s;
    }

    static inline int parseInt(const char *&token)
    {
        token += strspn(token, " \t");
        int i = atoi(token);
        token += strcspn(token, " \t\r");
        return i;
    }

    static bool tryParseDouble(const char *s, const char *s_end, double *result)
    {
        if (s >= s_end)
        {
            return false;
        }

        double mantissa = 0.0;
        // This exponent is base 2 rather than 10.
        // However the exponent we parse is supposed to be one of ten,
        // thus we must take care to convert the exponent/and or the
        // mantissa to a * 2^E, where a is the mantissa and E is the
        // exponent.
        // To get the final double we will use ldexp, it requires the
        // exponent to be in base 2.
        int exponent = 0;

        // NOTE: THESE MUST BE DECLARED HERE SINCE WE ARE NOT ALLOWED
        // TO JUMP OVER DEFINITIONS.
        char sign = '+';
        char exp_sign = '+';
        char const *curr = s;

        // How many characters were read in a loop.
        int read = 0;
        // Tells whether a loop terminated due to reaching s_end.
        bool end_not_reached = false;

        /*
         BEGIN PARSING.
         */

        // Find out what sign we've got.
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
    static inline float parseFloat(const char *&token)
    {
        token += strspn(token, " \t");
#ifdef TINY_OBJ_LOADER_OLD_FLOAT_PARSER
        float f = (float)utils::atof(token);
        token += strcspn(token, " \t\r");
#else
        const char *end = token + strcspn(token, " \t\r");
        double val = 0.0;
        tryParseDouble(token, end, &val);
        float f = static_cast<float>(val);
        token = end;
#endif
        return f;
    }
    static inline void parseFloat2(float &x, float &y, const char *&token)
    {
        x = parseFloat(token);
        y = parseFloat(token);
    }

    static inline void parseFloat3(float &x, float &y, float &z,
                                   const char *&token)
    {
        x = parseFloat(token);
        y = parseFloat(token);
        z = parseFloat(token);
    }

    // Parse triples: i, i/j/k, i//k, i/j
    static vertex_index parseTriple(const char *&token, int vsize, int vnsize,
                                    int vtsize)
    {
        vertex_index vi(-1);

        vi.v_idx = fixIndex(atoi(token), vsize);
        token += strcspn(token, "/ \t\r");
        if (token[0] != '/')
        {
            return vi;
        }
        token++;

        // i//k
        if (token[0] == '/')
        {
            token++;
            vi.vn_idx = fixIndex(atoi(token), vnsize);
            token += strcspn(token, "/ \t\r");
            return vi;
        }

        // i/j/k or i/j
        vi.vt_idx = fixIndex(atoi(token), vtsize);
        token += strcspn(token, "/ \t\r");
        if (token[0] != '/')
        {
            return vi;
        }

        // i/j/k
        token++; // skip '/'
        vi.vn_idx = fixIndex(atoi(token), vnsize);
        token += strcspn(token, "/ \t\r");
        return vi;
    }

    static inline bool operator<(const vertex_index &a, const vertex_index &b)
    {
        if (a.v_idx != b.v_idx)
            return (a.v_idx < b.v_idx);
        if (a.vn_idx != b.vn_idx)
            return (a.vn_idx < b.vn_idx);
        if (a.vt_idx != b.vt_idx)
            return (a.vt_idx < b.vt_idx);

        return false;
    }

    static std::string &replacePathSeperator(std::string &path)
    {
        for (std::string::size_type i = 0, size = path.size(); i < size; ++i)
        {
            if (path[i] == '\\')
                path[i] = '/';
        }
        return path;
    }

} // namespace GameEngine

#endif // _TINY_OBJ_LOADER_H
