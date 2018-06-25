#ifndef PATTERN_POLAR_RATE_TILE_HPP_
#define PATTERN_POLAR_RATE_TILE_HPP_

namespace aff3ct
{
namespace tools
{
class Pattern_polar_tile : public Pattern_polar_i
{
public:
	const uint8_t TILE = static_cast<uint8_t>(polar_node_t::SPC) +1;

protected:
	Pattern_polar_tile(const int &N, const Binary_node<Pattern_polar_i>* node,
	                 const int min_level = 3, const int max_level = 3)
	: Pattern_polar_i(N, node, min_level, max_level)
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
	Pattern_polar_tile(const int level = 3)
	: Pattern_polar_i(level, level)
	{
	}

	virtual Pattern_polar_i* alloc(const int &N, const Binary_node<Pattern_polar_i>* node) const
	{
		return new Pattern_polar_tile(N, node, min_level, max_level);
	}

	virtual ~Pattern_polar_tile() {}

	virtual polar_node_t type()       const { return static_cast<polar_node_t>(TILE); }
	virtual std::string  name()       const { return "Tile";             }
	virtual std::string  short_name() const { return "t";                 }
	virtual std::string  fill_color() const { return "#AD7FA8";            }
	virtual std::string  font_color() const { return "#FFFFFF";            }

	virtual std::string f() const { return ""; }
	virtual std::string g() const { return ""; }
	virtual std::string h() const { return ""; }

	virtual std::string apply_h(std::string start_indent = "", std::string str_off_l = "", std::string str_off_s = "") const
	{
		std::stringstream stream;

		stream << tab << "_TCE_POLAR_TILE8(l_c, f_b[" <<  (this->off_s >> 3) << "], s[" << (this->off_s >> 6) << "][" << ((this->off_s >> 3) & 7) << "]);";
		stream << std::endl;

		return  stream.str();
	}

	virtual int _match(const int &reverse_graph_depth, const Binary_node<Pattern_polar_i>* node_curr) const
	{
		return (reverse_graph_depth == 3) ? 30 : 0;
	}

	virtual bool is_terminal() const { return true; }
};
}
}

#endif /* PATTERN_POLAR_RATE_TILE_HPP_ */
