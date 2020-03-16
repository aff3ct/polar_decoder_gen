#ifndef PATTERN_POLAR_TTA_SC_SPC_HPP_
#define PATTERN_POLAR_TTA_SC_SPC_HPP_

#include <aff3ct.hpp>

namespace aff3ct
{
namespace tools
{
class Pattern_polar_TTA_SC_spc : public Pattern_polar_spc
{
protected:
	Pattern_polar_TTA_SC_spc(const int &N, const Binary_node<Pattern_polar_i>* node,
	                     const int min_level = 2, const int max_level = -1)
	: Pattern_polar_spc(N, node, min_level, max_level)
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
	Pattern_polar_TTA_SC_spc(const int min_level = 2, const int max_level = -1)
	: Pattern_polar_spc(min_level, max_level) {}

	virtual ~Pattern_polar_TTA_SC_spc() {}

	virtual Pattern_polar_TTA_SC_spc* alloc(const int &N, const Binary_node<Pattern_polar_i>* node) const
	{
		if (node == nullptr)
			return new Pattern_polar_TTA_SC_spc(this->min_level, this->max_level);
		else
			return new Pattern_polar_TTA_SC_spc(N, node, this->min_level, this->max_level);
	}

	virtual std::string apply_f(std::string start_indent = "", std::string str_off_l = "", std::string str_off_s = "") const
	{
		return "";
	}

	virtual std::string apply_g(std::string start_indent = "", std::string str_off_l = "", std::string str_off_s = "") const
	{
		return "";
	}

	virtual std::string apply_h(std::string start_indent = "", std::string str_off_l = "", std::string str_off_s = "") const
	{
		if (str_off_l.empty()) str_off_l = std::to_string(this->off_l);
		if (str_off_s.empty()) str_off_s = std::to_string(this->off_s);

		auto apply_spc = h();
		std::string spaces = ""; for (auto i = 0; i < 2*this->n_dig+1; i++) spaces += " ";

		std::stringstream stream;
		stream << "API_polar::template "  << apply_spc  << "<" << std::setw(this->n2_dig) << this->size << ">("
		       << "s, "
		       << "l, "
		       << std::setw(this->n_dig ) << str_off_l  << "+" << std::setw(this->n_dig ) << 0          << ", "
		       << spaces                                                                                << "  "
		       << spaces                                                                                << "  "
		       << std::setw(this->n_dig ) << str_off_s  << "+" << std::setw(this->n_dig ) << 0          << ", "
		       << std::setw(this->n2_dig) << this->size << ");" << std::endl;

		return stream.str();
	}
};
}
}

#endif /* PATTERN_POLAR_TTA_SC_SPC_HPP_ */
