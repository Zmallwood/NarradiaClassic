#!/usr/bin/perl

use Math::Trig;
use Math::Vec;

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
        $world_area_width = 100;
        $world_area_height = 100;
        $tile_size = 2.0;
        $elev_amount = 11.0;

        open(DATA, ">World.conf") or die "Couldn't open file World.conf, $!";

        print DATA "Width=$world_width\n";
        print DATA "Height=$world.height\n";

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

        for ($wy = 0; $wy < $world.height; $wy = $wy + 1) {
            for ($wx = 0; $wx < $world_width; $wx = $wx + 1) {
                for ($way = 0; $way < $world_area_height; $way = $way + 1) {
                    for ($wax = 0; $wax < $world_area_width; $wax = $wax + 1) {
                        $global_x = $wx*$world_area_width + $wax;
                        $global_y = $wy*$world_area_height+ $way;

                        $tiles[$global_x][$global_y] = "GroundWater";
                        $elevs[$global_x][$global_y] = 0.0;
                        $reds[$global_x][$global_y] = 0.0;
                        $greens[$global_x][$global_y] = 0.75;
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
        $num_tiles_y = $world.height*$world_area_height;
        $max_side = $num_tiles_x > $num_tiles_y ? $num_tiles_x : $num_tiles_y;
        print "Max side: $max_side\n";
        $r_cont = $max_side/2*80/100;
        $r = $r_cont;
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
                    $greens[$x][$y] = 0.8;
                    $reds[$x][$y] = 0.0;
                    $blues[$x][$y] = 0.3;
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

                    if ($xx < 0 or $xx >= $num_tiles_x or $yy < 0 or $yy >= $num_tiles_y) {
                        next;
                    }

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

        # Generate hills

        print "Generate elevation: large hills\n";

        $num_large_hills = 5 + int(rand(5));

        for ($i = 0; $i < $num_large_hills; $i = $i + 1) {
            $x_cent = int(rand($num_tiles_x));
            $y_cent = int(rand($num_tiles_y));
            $r_max = 50 + int(rand(100));
            $elev_inc = 0.05 + rand(1)/5.0;


            for ($r = $r_max; $r >= 0; $r = $r - 1) {
                for ($y = $y_cent - $r; $y <= $y_cent + $r; $y = $y + 1) {
                    for ($x = $x_cent - $r; $x <= $x_cent + $r; $x = $x + 1) {

                        if ($x < 0 or $x >= $num_tiles_x or $y < 0 or $y >= $num_tiles_y) {
                            next;
                        }

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

        $num_small_hills = 50 + int(rand(50));

        for ($i = 0; $i < $num_small_hills; $i = $i + 1) {
            $x_cent = int(rand($num_tiles_x));
            $y_cent = int(rand($num_tiles_y));
            $r_max = 20 + int(rand(50));
            $elev_inc = 0.05 + rand(1)/6.0;

            if ($i % ($num_small_hills/10) == 0) {
                $progress = int($i / $num_small_hills *100);
                print "$progress %\n";
            }

            for ($r = $r_max; $r >= 0; $r = $r - 1) {
                for ($y = $y_cent - $r; $y <= $y_cent + $r; $y = $y + 1) {
                    for ($x = $x_cent - $r; $x <= $x_cent + $r; $x = $x + 1) {

                        if ($x < 0 or $x >= $num_tiles_x or $y < 0 or $y >= $num_tiles_y) {
                            next;
                        }

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

        print "Generate elevation: small elevs\n";

        $num_small_elevs = 300 + int(rand(50));

        for ($i = 0; $i < $num_small_elevs; $i = $i + 1) {
            $x_cent = int(rand($num_tiles_x));
            $y_cent = int(rand($num_tiles_y));
            $r_max = 5 + int(rand(5));
            $elev_inc = 0.05 + rand(1)/6.0;

            if ($i % ($num_small_elevs/10) == 0) {
                $progress = int($i / $num_small_elevs *100);
                print "$progress %\n";
            }

            for ($r = $r_max; $r >= 0; $r = $r - 1) {
                for ($y = $y_cent - $r; $y <= $y_cent + $r; $y = $y + 1) {
                    for ($x = $x_cent - $r; $x <= $x_cent + $r; $x = $x + 1) {

                        if ($x < 0 or $x >= $num_tiles_x or $y < 0 or $y >= $num_tiles_y) {
                            next;
                        }

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

        # Generate per tile elev

        print "Generate elevation: per tile\n";

        for ($y = 0; $y < $num_tiles_y; $y = $y + 1) {
            for ($x = 0; $x < $num_tiles_x; $x = $x + 1) {

                if (($y*$num_tiles_x + $x) % (($num_tiles_x*$num_tiles_y)/10) == 0) {
                    $progress = int(($y*$num_tiles_x + $x) / ($num_tiles_x*$num_tiles_y) *100);
                    print "$progress %\n";
                }

                if ($tiles[$x][$y] ne "GroundWater") {
                    $elevs[$x][$y] = $elevs[$x][$y] + rand(0.15) - rand(0.15);
                }
            }
        }

        # Generate mountain ridge

        print "Generate mountain ridge\n";

        $start_coord_chosen = "no";

        my $ridge_start_x;
        my $ridge_start_y;

        while ($start_coord_chosen eq "no") {
            $ridge_start_x = int(rand($num_tiles_x));
            $ridge_start_y = int(rand($num_tiles_y));

            $dx = $ridge_start_x - $num_tiles_x/2;
            $dy = $ridge_start_y - $num_tiles_y/2;

            if ((($dx*$dx + $dy*$dy) <= $r_cont*$r_cont) and (($dx*$dx + $dy*$dy) > $r_cont*$r_cont*0.4*0.4)) {
                if ($tiles[$ridge_start_x][$ridge_start_y] ne "GroundWater") {
                    $start_coord_chosen = "yes";
                }
            }
        }

        print "ridge_start_x: $ridge_start_x\n";
        print "ridge_start_y: $ridge_start_y\n";

        $dx = $num_tiles_x/2 - $ridge_start_x;
        $dy = $num_tiles_y/2 - $ridge_start_y;

        $absdx = abs($dx);
        $absdy = abs($dy);

        $absmax = $absdx > $absdy ? $absdx : $absdy;

        $normx = $dx/$absmax;
        $normy = $dy/$absmax;

        $xstep = $normx != 0 ? $normx*5 : (rand(3) - 1);
        $ystep = $normy != 0 ? $normy*5 : (rand(3) - 1);

        $dxstep = (rand(3) - 1);
        $dystep = (rand(3) - 1);

        $dr = (rand(3) - 1);
        $ddr = -1*$dr/10.0;

        $ridge_num_steps = 200;

        $x = $ridge_start_x;
        $y = $ridge_start_y;

        $ridge_r = 30 + int(rand(20));

        $elev_inc = 0.05;

        for ($i = 0; $i < $ridge_num_steps; $i = $i + 10) {

            if ($i % 60 == 0) {
                $xstep = $xstep + $dxstep;
                $ystep = $ystep + $dystep;
            }

            for ($r_local = $ridge_r; $r_local >= 0; $r_local = $r_local - 1) {
                for ($yy = $y - $r_local; $yy <= $y + $r_local; $yy = $yy + 1) {
                    for ($xx = $x - $r_local; $xx <= $x + $r_local; $xx = $xx + 1) {

                        if ($xx < 0 || $yy < 0 || $xx >= $num_tiles_x || $yy >= $num_tiles_y) {
                            next;
                        }

                        if ($tiles[$xx][$yy] eq "GroundWater") {
                            next;
                        }

                        $dx = $xx - $x;
                        $dy = $yy - $y;

                        if ($dx*$dx + $dy*$dy <= $r_local*$r_local) {
                            $elevs[$xx][$yy] = $elevs[$xx][$yy] + $elev_inc;
                            $tiles[$xx][$yy] = "Ground";
                            $objects[$xx][$yy] = "";
                            $reds[$xx][$yy] = 0.5;
                            $greens[$xx][$yy] = 0.8;
                            $blues[$xx][$yy] = 0.6;
                        }
                    }
                }
            }

            #$ridge_r = $ridge_r + $dr;
            #$dr = $dr + $ddr;

            $x = int($x + $xstep*10);
            $y = int($y + $ystep*10);
        }

        # Generate colors variations

        print "Generate color variations: Large\n";

        $num_color_variations_large = 20 + int(rand(20));

        for ($i = 0; $i < $num_color_variations_large; $i = $i + 1) {

            if ($i % ($num_color_variations_large/10) == 0) {
                $progress = int($i / $num_color_variations_large *100);
                print "$progress %\n";
            }

            $x_cent = int(rand($num_tiles_x));
            $y_cent = int(rand($num_tiles_y));
            $r = 10 + int(rand(60));
            $elev_inc = 0.05 + rand(1)/6.0;
            $vary_type = int(rand(4));

            for ($y = $y_cent - $r; $y <= $y_cent + $r; $y = $y + 1) {
                for ($x = $x_cent - $r; $x <= $x_cent + $r; $x = $x + 1) {

                    if ($x < 0 or $x >= $num_tiles_x or $y < 0 or $y >= $num_tiles_y) {
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


        print "Generate color variations: Small\n";

        $num_color_variations_small = 200;

        for ($i = 0; $i < $num_color_variations_small; $i = $i + 1) {

            if ($i % ($num_color_variations_small/10) == 0) {
                $progress = int($i / $num_color_variations_small *100);
                print "$progress %\n";
            }

            $x_cent = int(rand($num_tiles_x));
            $y_cent = int(rand($num_tiles_y));
            $r = 5 + int(rand(10));
            $elev_inc = 0.05 + rand(1)/6.0;
            $vary_type = int(rand(4));

            for ($y = $y_cent - $r; $y <= $y_cent + $r; $y = $y + 1) {
                for ($x = $x_cent - $r; $x <= $x_cent + $r; $x = $x + 1) {

                    if ($x < 0 or $x >= $num_tiles_x or $y < 0 or $y >= $num_tiles_y) {
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

        # Generate lakes

        print "Generate lakes.\n";

        $num_lakes = 10 + int(rand(10));

        for ($i = 0; $i < $num_lakes; $i = $i + 1) {
            $x_cent = int(rand($num_tiles_x));
            $y_cent = int(rand($num_tiles_y));
            $r = 20 + int(rand(90));

            for ($y = $y_cent - $r; $y <= $y_cent + $r; $y = $y + 1) {
                for ($x = $x_cent - $r; $x <= $x_cent + $r; $x = $x + 1) {

                    if ($x < 0 or $x >= $num_tiles_x or $y < 0 or $y >= $num_tiles_y) {
                        next;
                    }

                    $dx = $x - $x_cent;
                    $dy = $y - $y_cent;
                    $r_local = sqrt($dx*$dx + $dy*$dy);

                    if ($dx*$dx + $dy*$dy <= $r*$r) {
                        if ($elevs[$x][$y] < 2.0) {
                            $tiles[$x][$y] = "GroundWater";
                            $reds[$x][$y] = 0.0;
                            $greens[$x][$y] = 0.75;
                            $blues[$x][$y] = 1.0;
                            $elevs[$x][$y] = 0.0;
                            $objects[$x][$y] = "";
                        }
                    }
                }
            }
        }

        # Generate rivers

        print "Generate rivers\n";

        $num_rivers = 60;

        for ($i = 0; $i < $num_rivers; $i = $i + 1) {
            $x = int(rand($num_tiles_x));
            $y = int(rand($num_tiles_y));
            $xstep = rand(3) - 1.0;
            $ystep = rand(3) - 1.0;

            $riv_len = 100 + int(rand(400));

            for ($j = 0; $j < $riv_len; $j = $j + 1) {
                if ($tiles[$x][$y] eq "Ground") {
                    if ($x >= 0 and $x >= 0 and $x < $num_tiles_x - 1 and $y < $num_tiles_y - 1) {
                        $tiles[$x][$y] = "GroundRiver";

                        $reds[$x][$y]= 0.0;
                        $greens[$x][$y]= 0.75;
                        $blues[$x][$y]= 1.0;

                        $reds[$x + 1][$y]= 0.0;
                        $greens[$x + 1][$y]= 0.75;
                        $blues[$x + 1][$y]= 1.0;

                        $reds[$x + 1][$y + 1]= 0.0;
                        $greens[$x + 1][$y + 1]= 0.75;
                        $blues[$x + 1][$y + 1]= 1.0;

                        $reds[$x][$y + 1]= 0.0;
                        $greens[$x][$y + 1]= 0.75;
                        $blues[$x][$y + 1]= 1.0;

                        $objects[$x][$x] = "";
                    }
                }

                $x = $x + $xstep;
                $y = $y + $ystep;
            }
        }

        # Generate misc objects

        print "Generate misc objects\n";

        $num_tree1s = 18000;

        for ($i = 0; $i < $num_tree1s; $i = $i + 1) {
            $x = int(rand($num_tiles_x));
            $y = int(rand($num_tiles_y));

            if ($tiles[$x][$y] eq "Ground") {
                if ($reds[$x][$y] < 0.6 and $blues[$x][$y] < 0.6) {
                    $objects[$x][$y] = "ObjectTree1";
                }
            }
        }

        $num_tree2s = 18000;

        for ($i = 0; $i < $num_tree2s; $i = $i + 1) {
            $x = int(rand($num_tiles_x));
            $y = int(rand($num_tiles_y));

            if ($tiles[$x][$y] eq "Ground") {
                if ($reds[$x][$y] < 0.6 and $blues[$x][$y] < 0.6) {
                    $objects[$x][$y] = "ObjectTree2";
                }
            }
        }

        $num_bush1s = 18000;

        for ($i = 0; $i < $num_bush1s; $i = $i + 1) {
            $x = int(rand($num_tiles_x));
            $y = int(rand($num_tiles_y));

            if ($tiles[$x][$y] eq "Ground") {
                if ($reds[$x][$y] < 0.6 and $blues[$x][$y] < 0.6) {
                    $objects[$x][$y] = "ObjectBush1";
                }
            }
        }

        $num_stone_boulders = 18000;

        for ($i = 0; $i < $num_stone_boulders; $i = $i + 1) {
            $x = int(rand($num_tiles_x));
            $y = int(rand($num_tiles_y));

            if ($tiles[$x][$y] eq "Ground") {
                $objects[$x][$y] = "ObjectStoneBoulder";
            }
        }

        # Calculating normals

        print "Calculating normals\n";

        for ($y = 0; $y < $num_tiles_y - 1; $y = $y + 1) {
            for ($x = 0; $x < $num_tiles_x - 1; $x = $x + 1) {

                if (($y*$num_tiles_x + $x) % (($num_tiles_x*$num_tiles_y)/10) == 0) {
                    $progress = int(($y*$num_tiles_x + $x) / ($num_tiles_x*$num_tiles_y) *100);
                    print "$progress %\n";
                }

                $v = Math::Vec->new(0, 0, 0);
                $A = Math::Vec->new($tile_size,$elevs[$x + 1][$y]*$elev_amount - $elevs[$x][$y]*$elev_amount,0);
                $B = Math::Vec->new(0,$elevs[$x][$y + 1]*$elev_amount- $elevs[$x][$y]*$elev_amount,$tile_size);
                @normal = $v->PlaneUnitNormal($A, $B);
                $normalsx[$x][$y] = $normal[0];
                $normalsy[$x][$y] = -$normal[1];
                $normalsz[$x][$y] = $normal[2];
            }
        }

        # Writing to files

        for ($wy = 0; $wy < $world.height; $wy = $wy + 1) {
            for ($wx = 0; $wx < $world_width; $wx = $wx + 1) {
                print ">Writing file for world area at: ($wx, $wy)\n";

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
