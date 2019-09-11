#ifndef GENERATOR_POLAR_GPP
#define GENERATOR_POLAR_GPP

#include <vector>
#include <string>
#include <iostream>
#include <aff3ct.hpp>

#include "../Generator_polar.hpp"

namespace aff3ct
{
namespace generator
{
class Generator_polar_GPP : public Generator_polar
{
public:
	Generator_polar_GPP(const int& K,
	                    const int& N,
	                    const float& snr,
	                    const std::vector<bool>& frozen_bits,
	                    const std::vector<tools::Pattern_polar_i*> &patterns,
	                    const int idx_r0,
	                    const int idx_r1,
	                    std::string mother_class_name,
	                    std::string MOTHER_CLASS_NAME,
	                    std::ostream &dec_stream         = std::cout,
	                    std::ostream &short_dec_stream   = std::cout,
	                    std::ostream &graph_stream       = std::cout,
	                    std::ostream &short_graph_stream = std::cout,
	                    const bool enable_short_decoder  = true);
	virtual ~Generator_polar_GPP();

protected:
	void generate_header(const std::string        mother_class_name,
	                     const std::vector<bool>& frozen_bits,
	                     const std::string        fbits_name,
	                           std::ostream       &stream);

	virtual void generate_class_header(const std::string class_name,
	                                   const std::string fbits_name,
	                                         std::ostream &stream1,
	                                         std::ostream &stream2) = 0;

	virtual void generate_class_footer(std::ostream &stream) = 0;
	        void generate_footer      (std::ostream &stream);

	virtual void recursive_generate_decoder      (const tools::Binary_node<tools::Pattern_polar_i>* node_curr, std::ostream &stream) = 0;
	virtual void recursive_generate_short_decoder(const tools::Binary_node<tools::Pattern_polar_i>* node_curr, std::ostream &stream) = 0;
};
}
}

#endif /* GENERATOR_POLAR_GPP */
