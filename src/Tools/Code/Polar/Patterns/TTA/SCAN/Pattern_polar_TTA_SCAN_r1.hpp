#ifndef PATTERN_POLAR_TTA_SCAN_RATE_1_HPP_
#define PATTERN_POLAR_TTA_SCAN_RATE_1_HPP_

#include <aff3ct.hpp>

namespace aff3ct
{
namespace tools
{
class Pattern_polar_TTA_SCAN_r1 : public Pattern_polar_r1
{
protected:
	Pattern_polar_TTA_SCAN_r1(const int &N, const Binary_node<Pattern_polar_i>* node,
	                    const int min_level = 0, const int max_level = -1)
	: Pattern_polar_r1(N, node, min_level, max_level)
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
	Pattern_polar_TTA_SCAN_r1(const int min_level = 0, const int max_level = -1)
	: Pattern_polar_r1(min_level, max_level) {}

	virtual ~Pattern_polar_TTA_SCAN_r1() {}

	virtual Pattern_polar_i* alloc(const int &N, const Binary_node<Pattern_polar_i>* node) const
	{
		return new Pattern_polar_TTA_SCAN_r1(N, node, this->min_level, this->max_level);
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

		std::stringstream stream;
		int code = (3 << 16) | (this->size >> 3);

		if (this->si_2 < 64)
		{
			stream << "_TCE_LDOFF(" << str_off_l << ", l_a);" << std::endl;
			stream << tab << "_TCE_POLAR_LEAF(l_a, s[" << (this->off_s >> 6) << "], " << (this->off_s >> 3);
			stream << ", 0x" << std::hex << code << std::dec << ", s[" << (this->off_s >> 6) << "]);";
			stream << std::endl;
		}
		else // n_elm
		{
			for ( auto i = 0; (64 * i) < this->size; i++)
			{
				if(i)
					stream << tab;
				stream << "_TCE_LDOFF(" << (this->off_l + i * 64) << ", l_a);" << std::endl;
				stream << tab << "_TCE_POLAR_LEAF(l_a, s[" << ((this->off_s >> 6) + i) << "], " << (this->off_s >> 3);
				stream << ", 0x" << std::hex << code << std::dec << ", s[" << ((this->off_s >> 6) + i) << "]);";
				stream << std::endl;
			}
		}

		return stream.str();
	}
};
}
}

#endif /* PATTERN_POLAR_TTA_SCAN_RATE_1_HPP_ */
