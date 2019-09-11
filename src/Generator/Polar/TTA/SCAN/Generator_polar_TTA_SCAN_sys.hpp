#ifndef GENERATOR_POLAR_TTA_SCAN_SYS_
#define GENERATOR_POLAR_TTA_SCAN_SYS_

#include <vector>
#include <string>
#include <iostream>
#include <aff3ct.hpp>

#include "../Generator_polar_TTA.hpp"

namespace aff3ct
{
namespace generator
{
class Generator_polar_TTA_SCAN_sys : public Generator_polar_TTA
{
private:
	const int n_ite;
public:
	Generator_polar_TTA_SCAN_sys(const int& K,
	                             const int& N,
	                             const int& n_ite,
	                             const float& snr,
	                             const std::vector<bool>& frozen_bits,
	                             const std::vector<tools::Pattern_polar_i*> &patterns,
	                             const int idx_r0,
	                             const int idx_r1,
	                             std::ostream &dec_stream         = std::cout,
	                             std::ostream &short_dec_stream   = std::cout,
	                             std::ostream &graph_stream       = std::cout,
	                             std::ostream &short_graph_stream = std::cout);
	virtual ~Generator_polar_TTA_SCAN_sys();

protected:
	void generate_class_header(const std::string class_name,
	                           const std::string fbits_name,
	                                 std::ostream &stream1,
	                                 std::ostream &stream2);
	void generate_class_footer(      std::ostream &stream);

	void recursive_generate_decoder      (const tools::Binary_node<tools::Pattern_polar_i>* node_curr, std::ostream &stream);
	void recursive_generate_short_decoder(const tools::Binary_node<tools::Pattern_polar_i>* node_curr, std::ostream &stream);
};
}
}

#endif /* GENERATOR_POLAR_TTA_SCAN_SYS_ */
