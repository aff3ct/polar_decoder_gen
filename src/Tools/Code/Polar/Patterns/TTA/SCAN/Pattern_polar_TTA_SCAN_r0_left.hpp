#ifndef PATTERN_POLAR_TTA_SCAN_RATE_0_LEFT_HPP_
#define PATTERN_POLAR_TTA_SCAN_RATE_0_LEFT_HPP_

#include <aff3ct.hpp>

namespace aff3ct
{
namespace tools
{
class Pattern_polar_TTA_SCAN_r0_left : public Pattern_polar_r0_left
{
protected:
	Pattern_polar_TTA_SCAN_r0_left(const int &N, const Binary_node<Pattern_polar_i>* node,
	                         const int min_level = 1, const int max_level = -1)
	: Pattern_polar_r0_left(N, node, min_level, max_level)
	{
		auto n_elm_2 = this->N / 2;
		auto local_off_l = 0;

		for (auto layer = this->m; layer > (this->m - node->get_depth()); layer--)
		{
			if ((n_elm_2 * 2) > 64)
				local_off_l += n_elm_2 * 2;
			else
				local_off_l += 64;
			n_elm_2 /= 2;
		}

		const int *p_off_l = &off_l;
		*const_cast<int*>(p_off_l) = local_off_l;
	}

public:
	Pattern_polar_TTA_SCAN_r0_left(const int min_level = 1, const int max_level = -1)
	: Pattern_polar_r0_left(min_level, max_level) {}

	virtual ~Pattern_polar_TTA_SCAN_r0_left() {}

	virtual Pattern_polar_TTA_SCAN_r0_left* alloc(const int &N, const Binary_node<Pattern_polar_i>* node) const
	{
		if (node == nullptr)
			return new Pattern_polar_TTA_SCAN_r0_left(this->min_level, this->max_level);
		else
			return new Pattern_polar_TTA_SCAN_r0_left(N, node, this->min_level, this->max_level);
	}

	virtual std::string apply_f(std::string start_indent = "", std::string str_off_l = "", std::string str_off_s = "") const
	{
		return "";
	}

	virtual std::string apply_g(std::string start_indent = "", std::string str_off_l = "", std::string str_off_s = "") const
	{
		// using namespace std;
		if (str_off_l.empty()) str_off_l = std::to_string(this->off_l);
		if (str_off_s.empty()) str_off_s = std::to_string(this->off_s);

		auto apply_g0 = g() + " ";
		std::string spaces = ""; for (auto i = 0; i < 2*this->n_dig+1; i++) spaces += " ";

		std::stringstream stream;
		stream << "API_polar::template "  << apply_g0   << "<" << std::setw(this->n2_dig) << this->si_2 << ">("
		       << "   "
		       << "l, "
		       << std::setw(this->n_dig ) << str_off_l  << "+" << std::setw(this->n_dig ) << 0          << ", "
		       << std::setw(this->n_dig ) << str_off_l  << "+" << std::setw(this->n_dig ) << this->si_2 << ", "
		       << spaces                                                                                << "  "
		       << std::setw(this->n_dig ) << str_off_l  << "+" << std::setw(this->n_dig ) << this->size << ", "
		       << std::setw(this->n2_dig) << this->si_2 << ");" << std::endl;

		return stream.str();
	}

	virtual std::string apply_h(std::string start_indent = "", std::string str_off_l = "", std::string str_off_s = "") const
	{
		if (str_off_l.empty()) str_off_l = std::to_string(this->off_l);
		if (str_off_s.empty()) str_off_s = std::to_string(this->off_s);

		auto apply_xo0 = h();
		std::string spaces = ""; for (auto i = 0; i < 2*this->n_dig+1; i++) spaces += " ";

		std::stringstream stream;
		stream << "API_polar::template "  << apply_xo0  << "<" << std::setw(this->n2_dig) << this->si_2 << ">("
		       << "s, "
		       << "   "
		       << std::setw(this->n_dig ) << str_off_s  << "+" << std::setw(this->n_dig ) << this->si_2 << ", "
		       << spaces                                                                                << "  "
		       << spaces                                                                                << "  "
		       << std::setw(this->n_dig ) << str_off_s  << "+" << std::setw(this->n_dig ) << 0          << ", "
		       << std::setw(this->n2_dig) << this->si_2 << ");" << std::endl;

		return stream.str();
	}
};
}
}

#endif /* PATTERN_POLAR_TTA_SCAN_RATE_0_LEFT_HPP_ */
