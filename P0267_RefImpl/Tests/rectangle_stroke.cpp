#include "catch.hpp"
#include <io2d.h>
#include "comparison.h"

using namespace std;
using namespace std::experimental;
using namespace std::experimental::io2d;

TEST_CASE("IO2D properly strokes a rectangle")
{
    auto reference = "stroked_rectangle_300x200.png";
    auto image = image_surface{format::argb32, 300, 200};
    image.paint( brush{rgba_color::red} );
    auto b = brush{rgba_color::blue};

    SECTION("Draw via rel_lines") {
        auto pb = path_builder{};
        pb.new_figure({50.f, 50.f});
        pb.rel_line({200.f, 0.f});
        pb.rel_line({0.f, 100.f});
        pb.rel_line({-200.f, 0.f});
        pb.rel_line({0.f, -100.f});
        pb.close_figure();
        image.stroke(b, pb);
    }
    
    SECTION("Draw via abs_lines") {
        auto pb = path_builder{};
        pb.new_figure({50.f, 50.f});
        pb.line({250.f, 50.f});
        pb.line({250.f, 150.f});
        pb.line({50.f, 150.f});
        pb.line({50.f, 50.f});
        pb.close_figure();
        image.stroke(b, pb);
    }

    SECTION("Draw via rel_lines with a translate matrix") {
        auto pb = path_builder{};
        pb.matrix(matrix_2d::init_translate({50.f, 50.f}));
        pb.new_figure({0.f, 0.f});
        pb.rel_line({200.f, 0.f});
        pb.rel_line({0.f, 100.f});
        pb.rel_line({-200.f, 0.f});
        pb.rel_line({0.f, -100.f});
        pb.close_figure();
        image.stroke(b, pb);
    }
    
    SECTION("Draw via rel_lines with a scale matrix") {
        auto pb = path_builder{};
        pb.matrix(matrix_2d::init_scale({ 0.5f, 2.0f }));
        pb.new_figure({ 50.f, 50.f });
        pb.rel_line({ 400.f, 0.f });
        pb.rel_line({ 0.f, 50.f });
        pb.rel_line({ -400.f, 0.f });
        pb.rel_line({ 0.f, -50.f });
        pb.close_figure();
        image.stroke(b, pb);
    }

    SECTION("Draw via abs_lines with a scale matrix") {
        auto pb = path_builder{};
        pb.matrix(matrix_2d::init_scale({ 0.5f, 2.0f }));
        pb.new_figure({ 50.f, 50.f });
        pb.line({450.f, 50.f});
        pb.line({250.f, 100.f});
        pb.line({-150.f, 150.f});
        pb.line({50.f, 100.f});
        pb.close_figure();
        image.stroke(b, pb);
    }
    
    SECTION("Draw via rel separated lines") {
        auto rp = render_props{antialias::none};
        auto sp = stroke_props{2.f, line_cap::square};
        auto pb = path_builder{};
        pb.new_figure({ 50.f, 50.f });
        pb.rel_line({200.f, 0.f});
        image.stroke(b, pb, nullopt, sp, nullopt, rp);
        
        pb.clear();
        pb.new_figure({ 250.f, 50.f });
        pb.rel_line({0.f, 100.f});
        image.stroke(b, pb, nullopt, sp, nullopt, rp);

        pb.clear();
        pb.new_figure({ 250.f, 150.f });
        pb.rel_line({-200.f, 0.f});
        image.stroke(b, pb, nullopt, sp, nullopt, rp);

        pb.clear();
        pb.new_figure({ 50.f, 150.f });
        pb.rel_line({0.f, -100.f});
        image.stroke(b, pb, nullopt, sp, nullopt, rp);
    }
    
    CHECK( ComparePNGExact(image, reference) == true );
}
