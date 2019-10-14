#include "json/json.hpp"

#include <iostream>
#include <vector>
#include <array>
#include <cstdint>
#include <cstdio>

#include <iterator>
#include <algorithm>
#include <numeric>

#include "apcop2.h"


using speech_arr_t = std::array<std::int16_t, 2 * AMBE_WS_NOM>;


std::vector<speech_arr_t> read_pcm_file(char const * fname_p)
{
    std::vector<speech_arr_t> rv;

    FILE * ifile = fopen(fname_p, "rb");

    if (not ifile)
    {
        std::cerr << "Cannot open " << fname_p << " for reading\n";
    }
    else
    {
        fseek(ifile, 0, SEEK_END);
        auto fsize = ftell(ifile);
        rewind(ifile);

        auto nframes = fsize / sizeof (rv[0]);

        rv.resize(nframes);

        auto nread = fread(rv.data(), sizeof (rv[0]), nframes, ifile);
        if (nread != nframes)
        {
            std::cerr << "Failed to read " << nframes << " frames from input file, read " << nread << " instead.\n";
            rv.clear();
        }

        fclose(ifile);
    }

    return rv;
}


std::vector<std::uint64_t> encode_speech(std::vector<speech_arr_t> &speech_vec)
{
    ENCSTATE_T es;
    FECSTATE_T efec;

    ambe_init_enc(&es, APCO_HR_MODE, 1);
    ambe_init_fec(&efec, APCO_HR_MODE);

    std::array<std::int16_t, APCO_HR_SRCBITS_NOM> ochan;
    std::vector<std::uint64_t> rv(speech_vec.size());

    std::transform(speech_vec.begin(), speech_vec.end(), rv.begin(),
        [&](speech_arr_t & sample)
        {
            ambe_voice_enc(
                ochan.data(),
                0,
                sample.data(),
                AMBE_WS_NOM,
                AMBE_TONE_DET_ENABLE_FLAG | AMBE_NS_ENABLE_FLAG | AMBE_DTX_ENABLE_FLAG,
                0,
                APCO_NS_GAIN_NOM,
                &es
            );

            ambe_voice_enc(
                ochan.data(),
                0,
                sample.data() + AMBE_WS_NOM,
                AMBE_WS_NOM,
                AMBE_TONE_DET_ENABLE_FLAG | AMBE_NS_ENABLE_FLAG | AMBE_DTX_ENABLE_FLAG,
                1,
                APCO_NS_GAIN_NOM,
                &es
            );

            std::uint64_t rv = std::accumulate(ochan.cbegin(), ochan.cend(), 0ULL,
                [](std::uint64_t acc, std::int16_t bit)
                {
                    return (acc << 1) | bit;
                }
            );
            rv |= (1ULL << 63); // mark as 'valid frame' for serializing

            //printf("%016llX\n", rv);
            return rv;
        }
    );

    return rv;
}


int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "Please specify 8kHz mono 16-bit PCM input file\n";
        return -1;
    }

    auto speech_vec = read_pcm_file(argv[1]);

    auto const encoded_speech = encode_speech(speech_vec);

    nlohmann::json json;
    json["dvsi:ambep2"] = nlohmann::json(encoded_speech);

    std::cout << json.dump() << '\n';

    return 0;
}
