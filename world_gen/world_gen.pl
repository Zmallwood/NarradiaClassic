#!/usr/bin/perl

use Math::Trig;

# World generation script for Narradia

$running = "true";

while ($running eq "true") {
    print "Narradia World Generator\n";
    print "======================\n";
    print "1. Generate new world map\n";
    print "2. Exit\n";
    $menu_select = <STDIN>;
    chomp $menu_select;

    if ($menu_select == "1") {
        print "Generating world map...\n";

        $world_width = 6;
        $world_height = 6;
        $world_area_width = 300;
        $world_area_height = 300;

        open(DATA, ">World.conf") or die "Couldn't open file World.conf, $!";

        print DATA "Width=$world_width\n";
        print DATA "Height=$world_height\n";

        my $global_x;
        my $global_y;

        my @tiles;
        my @elevs;
        my @objects;
        my @reds;
        my @greens;
        my @blues;
        my @normalsx;
        my @normalsy;
        my @normalsz;

        # Generate sea

        for ($wy = 0; $wy < $world_height; $wy = $wy + 1) {
            for ($wx = 0; $wx < $world_width; $wx = $wx + 1) {
                for ($way = 0; $way < $world_area_height; $way = $way + 1) {
                    for ($wax = 0; $wax < $world_area_width; $wax = $wax + 1) {
                        $global_x = $wx*$world_area_width + $wax;
                        $global_y = $wy*$world_area_height+ $way;

                        $tiles[$global_x][$global_y] = "GroundWater";
                        $elevs[$global_x][$global_y] = 0.0;
                        $reds[$global_x][$global_y] = 1.0;
                        $greens[$global_x][$global_y] = 1.0;
                        $blues[$global_x][$global_y] = 1.0;
                        $normalsx[$global_x][$global_y] = 0.0;
                        $normalsy[$global_x][$global_y] = 1.0;
                        $normalsz[$global_x][$global_y] = 0.0;
                        $objects[$global_x][$global_y] = "";
                    }
                }
            }
        }
        $num_tiles_x = $world_width*$world_area_width;
        $num_tiles_y = $world_height*$world_area_height;
        $max_side = $num_tiles_x > $num_tiles_y ? $num_tiles_x : $num_tiles_y;
        print "Max side: $max_side\n";
        $r = $max_side/2*80/100;
        $r_varying = 50;
        $center_x = $num_tiles_x/2;
        $center_y = $num_tiles_y/2;

        # Generate continent

        print "Continent radius: $r\n";

        for ($y = $center_y - $r; $y <= $center_y + $r; $y = $y + 1) {
            for ($x = $center_x - $r; $x <= $center_x + $r; $x = $x + 1) {
                $dx = $x - $center_x;
                $dy = $y - $center_y;

                $r_local = $r + $r_varying;

                if ($dx != 0) {
                    $w = atan($dy/$dx);
                    $r_local = $r + int(cos($w*10 + 3)*$r_varying);
                }

                if ($dx*$dx + $dy*$dy < $r_local*$r_local) {
                    $tiles[$x][$y] = "Ground";
                    $reds[$x][$y] = 0.0;
                    $blues[$x][$y] = 0.0;
                }
            }
        }

        print "Generating trees.\n";

        $num_forests = 15 + int(rand(15));
        $num_trees_forest = 300 + int(rand(600));

        for ($i = 0; $i < $num_forests; $i = $i + 1) {
            $x = int(rand($num_tiles_x));
            $y = int(rand($num_tiles_y));

            for ($j = 0; $j < $num_trees_forest; $j = $j + 1) {
                $dx = $x - $center_x;
                $dy = $y - $center_y;

                if ($tiles[$x][$y] eq "Ground") {
                    if (int(rand(2)) == 0) {
                        $objects[$x][$y] = "ObjectTree1";
                    }
                    else {
                        $objects[$x][$y] = "ObjectTree2";
                    }
                }

                $x = $x + (int(rand(2)) == 1 ? 1 : -1) *(1 + int(rand(8)));
                $y = $y + (int(rand(2)) == 1 ? 1 : -1) *(1 + int(rand(8)));
            }
        }

        # Snow lands

        print "Generating snow lands.\n";

        $snow_lands_border = 0.25;
        $snow_lands_border_row =int($snow_lands_border*$num_tiles_y);

        print "Snow lands border at row $snow_lands_border_row.\n";

        for ($y = 0; $y < $snow_lands_border_row; $y = $y + 1) {
            for ($x = 0; $x < $num_tiles_x; $x = $x + 1) {
                $border_row_vary = $snow_lands_border_row + cos($x/50.0)*20 - 20;
                if ($y < $border_row_vary) {
                    if ($tiles[$x][$y] eq "Ground") {
                        $tiles[$x][$y] = "Ground";
                        $tiles[$x][$y] = "GroundSnow";
                        $objects[$x][$y] = "";
                        $reds[$x][$y] = 1.0;
                        $greens[$x][$y] = 1.0;
                        $blues[$x][$y] = 1.0;
                    }
                }
            }
        }

        # Deserts

        print "Generating deserts.\n";

        $deserts_border = 0.75;
        $deserts_border_row =int($deserts_border*$num_tiles_y);

        print "Deserts border at row $deserts_border_row.\n";

        for ($y = $deserts_border_row; $y < $num_tiles_y; $y = $y + 1) {
            for ($x = 0; $x < $num_tiles_x; $x = $x + 1) {
                $border_row_vary = $deserts_border_row + cos($x/50.0)*20 + 20;
                if ($y > $border_row_vary) {
                    if ($tiles[$x][$y] eq "Ground") {
                        $tiles[$x][$y] = "Ground";
                        $tiles[$x][$y] = "GroundSand";
                        $objects[$x][$y] = "";
                        $reds[$x][$y] = 1.0;
                        $greens[$x][$y] = 1.0;
                        $blues[$x][$y] = 1.0;
                    }
                }
            }
        }

        # Generate islands

        print "Generating islands\n";

        $num_islands = 8 + int(rand(8));

        for ($i = 0; $i < $num_islands; $i = $i + 1) {

            my $coord_at_sea = "no";

            my $x;
            my $y;

            while ($coord_at_sea eq "no") {

                $x = int(rand($num_tiles_x));
                $y = int(rand($num_tiles_y));

                $dx = $x - $center_x;
                $dy = $y - $center_y;

                $r_local = $r + $r_varying;

                if ($dx != 0) {
                    $w = atan($dy/$dx);
                    $r_local = $r + int(cos($w*10 + 3)*$r_varying);
                }

                if ($dx*$dx + $dy*$dy > $r_local*$r_local) {
                    $coord_at_sea = "yes";
                }
            }

            $r_island = 40 + int(rand(70));

            for ($yy = $y - $r_island; $yy <= $y + $r_island; $yy = $yy + 1) {
                for ($xx = $x - $r_island; $xx <= $x + $r_island; $xx = $xx + 1) {
                    $dx_isl = $xx - $x;
                    $dy_isl = $yy - $y;

                    if ($dx_isl*$dx_isl + $dy_isl*$dy_isl <= $r_island*$r_island) {
                        $tiles[$xx][$yy] = "Ground";
                        $reds[$xx][$yy] = 0.0;
                        $greens[$xx][$yy] = 1.0;
                        $blues[$xx][$yy] = 0.0;
                    }
                }
            }
        }

        # Generate elevation

        print "Generate elevation: large hills\n";

        $num_large_hills = 10 + int(rand(10));

        for ($i = 0; $i < $num_large_hills; $i = $i + 1) {
            $x_cent = int(rand($num_tiles_x));
            $y_cent = int(rand($num_tiles_y));
            $r_max = 50 + int(rand(100));
            $elev_inc = 0.05 + rand(1)/5.0;

            for ($r = $r_max; $r >= 0; $r = $r - 1) {
                for ($y = $y_cent - $r; $y <= $y_cent + $r; $y = $y + 1) {
                    for ($x = $x_cent - $r; $x <= $x_cent + $r; $x = $x + 1) {
                        $dx = $x - $x_cent;
                        $dy = $y - $y_cent;

                        if ($dx*$dx + $dy*$dy <= $r*$r) {
                            if ($tiles[$x][$y] ne "GroundWater") {
                                $elevs[$x][$y] = $elevs[$x][$y] + $elev_inc;
                            }
                        }
                    }
                }
            }
        }

        print "Generate elevation: small hills\n";

        $num_large_hills = 50 + int(rand(50));

        for ($i = 0; $i < $num_large_hills; $i = $i + 1) {
            $x_cent = int(rand($num_tiles_x));
            $y_cent = int(rand($num_tiles_y));
            $r_max = 20 + int(rand(50));
            $elev_inc = 0.05 + rand(1)/6.0;

            for ($r = $r_max; $r >= 0; $r = $r - 1) {
                for ($y = $y_cent - $r; $y <= $y_cent + $r; $y = $y + 1) {
                    for ($x = $x_cent - $r; $x <= $x_cent + $r; $x = $x + 1) {
                        $dx = $x - $x_cent;
                        $dy = $y - $y_cent;

                        if ($dx*$dx + $dy*$dy <= $r*$r) {
                            if ($tiles[$x][$y] ne "GroundWater") {
                                $elevs[$x][$y] = $elevs[$x][$y] + $elev_inc;
                            }
                        }
                    }
                }
            }
        }

        print "Generate mountain ridge\n";

        # Generate colors variations

        print "Generate color variations\n";

        $num_color_variations = 50 + int(rand(50));

        for ($i = 0; $i < $num_color_variations; $i = $i + 1) {
            $x_cent = int(rand($num_tiles_x));
            $y_cent = int(rand($num_tiles_y));
            $r = 40 + int(rand(160));
            $elev_inc = 0.05 + rand(1)/6.0;
            $vary_type = int(rand(4));

            for ($y = $y_cent - $r; $y <= $y_cent + $r; $y = $y + 1) {
                for ($x = $x_cent - $r; $x <= $x_cent + $r; $x = $x + 1) {

                    if ($x < 0 || $x >= $num_tiles_x || $y < 0 || $y >= $num_tiles_y) {
                        next;
                    }

                    $dx = $x - $x_cent;
                    $dy = $y - $y_cent;
                    $r_local = sqrt($dx*$dx + $dy*$dy);

                    if ($dx*$dx + $dy*$dy <= $r*$r) {
                        if ($tiles[$x][$y] ne "GroundWater") {
                            if ($vary_type == 0) {
                                $greens[$x][$y] = 1.0;
                                $reds[$x][$y] = ($reds[$x][$y] + 0.2)*1.05*(1.0 + ($r - $r_local)/$r);
                                $blues[$x][$y] = ($blues[$x][$y] + 0.3)*1.1*(1.0 + ($r - $r_local)/$r);
                            }
                            elsif ($vary_type == 1) {
                                $greens[$x][$y] = 1.0;
                                $reds[$x][$y] = $reds[$x][$y]*$r_local/$r + $greens[$x][$y]*($r - $r_local)/$r;
                            }
                            elsif ($vary_type == 2) {
                                $greens[$x][$y] = 1.0;
                                $blues[$x][$y] = $blues[$x][$y]*$r_local/$r + $greens[$x][$y]*($r - $r_local)/$r;
                            }
                            elsif ($vary_type == 3) {
                                $reds[$x][$y] = $reds[$x][$y]*($r_local + 30)/$r*1.5;
                                $greens[$x][$y] = 1.0;
                                $blues[$x][$y] = $blues[$x][$y]*($r_local + 30)/$r*1.5;
                            }

                            $reds[$x][$y] = $reds[$x][$y] < 0.0 ? 0.0 : $reds[$x][$y];
                            $greens[$x][$y] = $greens[$x][$y] < 0.0 ? 0.0 : $greens[$x][$y];
                            $blues[$x][$y] = $blues[$x][$y] < 0.0 ? 0.0 : $blues[$x][$y];

                            $reds[$x][$y] = $reds[$x][$y] > 0.6 ? 0.6 : $reds[$x][$y];
                            $greens[$x][$y] = $greens[$x][$y] > 1.0 ? 1.0 : $greens[$x][$y];
                            $blues[$x][$y] = $blues[$x][$y] > 0.8 ? 0.8 : $blues[$x][$y];
                        }
                    }
                }
            }
        }

        # Generate normals

        print "Generate normals\n";

        # Writing to files

        for ($wy = 0; $wy < $world_height; $wy = $wy + 1) {
            for ($wx = 0; $wx < $world_width; $wx = $wx + 1) {
                print ">Writing file for map ($wx, $wy)\n";

                print DATA "$wx,$wy=Map$wx\_$wy.map\n";

                open(DATA_AREA, ">Map$wx\_$wy.map") or die "Couldn't open file Map$wx\_$wy.map, $!";
                print DATA_AREA "<width>$world_area_width</width>\n";
                print DATA_AREA "<height>$world_area_height</height>\n";

                for ($way = 0; $way < $world_area_height; $way = $way + 1) {
                    for ($wax = 0; $wax < $world_area_width; $wax = $wax + 1) {
                        $global_x = $wx*$world_area_width + $wax;
                        $global_y = $wy*$world_area_height+ $way;

                        print DATA_AREA "<tile>\n";

                        print DATA_AREA "  <ground>$tiles[$global_x][$global_y]</ground>\n";

                        print DATA_AREA "  <elevation>";
                        printf DATA_AREA '%.3f', $elevs[$global_x][$global_y];
                        print DATA_AREA "f</elevation>\n";

                        print DATA_AREA "  <red>";
                        printf DATA_AREA '%.3f', $reds[$global_x][$global_y];
                        print DATA_AREA "f</red>\n";

                        print DATA_AREA "  <green>";
                        printf DATA_AREA '%.3f', $greens[$global_x][$global_y];
                        print DATA_AREA "f</green>\n";

                        print DATA_AREA "  <blue>";
                        printf DATA_AREA '%.3f', $blues[$global_x][$global_y];
                        print DATA_AREA "f</blue>\n";

                        print DATA_AREA "  <objects>\n";

                        if ($objects[$global_x][$global_y] ne "") {
                            print DATA_AREA "    <object>\n";
                            print DATA_AREA "      <type>$objects[$global_x][$global_y]</type>\n";
                            print DATA_AREA "      <quantity>1</quantity>\n";
                            print DATA_AREA "    </object>\n";
                        }

                        print DATA_AREA "  </objects>\n";

                        print DATA_AREA "  <normal>\n";

                        print DATA_AREA "    <x>";
                        printf DATA_AREA '%.3f', $normalsx[$global_x][$global_y];
                        print DATA_AREA "f</x>\n";

                        print DATA_AREA "    <y>";
                        printf DATA_AREA '%.3f', $normalsy[$global_x][$global_y];
                        print DATA_AREA "f</y>\n";

                        print DATA_AREA "    <z>";
                        printf DATA_AREA '%.3f', $normalsz[$global_x][$global_y];
                        print DATA_AREA "f</z>\n";

                        print DATA_AREA "  </normal>\n";

                        print DATA_AREA "</tile>\n";
                    }
                }

                close(DATA_AREA) || die "Couldn't close file properly";
            }
        }

        close(DATA) || die "Couldn't close file properly";

        $running = "false";
    }
    elsif ($menu_select == "2") {
        print "Exiting program.\n";
        $running = "false";
    }

}
