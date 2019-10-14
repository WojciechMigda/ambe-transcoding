#include "json/json.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <cstdint>

#include <iterator>
#include <algorithm>
#include <numeric>

#include "apcop2.h"


using speech_arr_t = std::array<std::int16_t, 2 * AMBE_WS_NOM>;


std::vector<std::uint64_t> read_json_file(char const * fname_p)
{
    std::vector<std::uint64_t> rv;

    nlohmann::json json;

    std::ifstream ifile(fname_p);

    if (ifile)
    {
        ifile >> json;

        if (json.count("dvsi:ambep2") != 1)
        {
            std::cerr << "Input file is missing \"dvsi:ambep2\" key\n";
        }
        else
        {
            auto vec = json["dvsi:ambep2"];

            rv.reserve(vec.size());
            vec.get_to<std::vector<std::uint64_t>>(rv);
        }
    }
    else
    {
        std::cerr << "Cannot open " << fname_p << " for reading\n";
    }

    return rv;
}


std::vector<speech_arr_t> decode_speech(std::vector<std::uint64_t> &encoded_speech)
{
    DECSTATE_T ds;
    FECSTATE_T dfec;

    ambe_init_dec(&ds, APCO_HR_MODE);
    ambe_init_fec(&dfec, APCO_HR_MODE);

    std::array<std::int16_t, APCO_HR_SRCBITS_NOM> ichan;
    std::vector<speech_arr_t> rv(encoded_speech.size());

    std::transform(encoded_speech.cbegin(), encoded_speech.cend(), rv.begin(),
        [&](std::uint64_t packed)
        {
            speech_arr_t rv;
            std::int16_t cmode = 0;

            if (packed & (1ULL << 63))
            {
                std::generate(ichan.rbegin(), ichan.rend(),
                    [&packed]()
                    {
                        auto rv = packed & 1;
                        packed >>= 1;
                        return rv;
                    }
                );
            }
            else
            {
                cmode |= AMBE_LOST_FRAME_FLAG;
            }


            auto const status = ambe_voice_dec(
                rv.data(),
                AMBE_WS_NOM,
                ichan.data(),
                0,
                cmode,
                0,
                &ds
            );

            ambe_voice_dec(
                rv.data() + AMBE_WS_NOM,
                AMBE_WS_NOM,
                ichan.data(),
                0,
                cmode,
                1,
                &ds
            );

            return rv;
        }
    );

    return rv;
}


int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "Please specify json-encoded AMBE+2 input file\n";
        return -1;
    }

    auto encoded_speech = read_json_file(argv[1]);
    auto speech_vec = decode_speech(encoded_speech);

//    FILE * ofile;
//    ofile = fopen("out.pcm", "wb");
//    fwrite(speech_vec.data(), sizeof (speech_vec[0]), speech_vec.size(), ofile);
//    fclose(ofile);

    return 0;
}
