#include <stdlib.h>
#include <zephyr/kernel.h>
#include "animation.h"

LV_IMG_DECLARE(crystal_01);
LV_IMG_DECLARE(crystal_02);
LV_IMG_DECLARE(crystal_03);
LV_IMG_DECLARE(crystal_04);
LV_IMG_DECLARE(crystal_05);
LV_IMG_DECLARE(crystal_06);
LV_IMG_DECLARE(crystal_07);
LV_IMG_DECLARE(crystal_08);
LV_IMG_DECLARE(crystal_09);
LV_IMG_DECLARE(crystal_10);
LV_IMG_DECLARE(crystal_11);
LV_IMG_DECLARE(crystal_12);
LV_IMG_DECLARE(crystal_13);
LV_IMG_DECLARE(crystal_14);
LV_IMG_DECLARE(crystal_15);
LV_IMG_DECLARE(crystal_16);
/* Custom static art added alongside the originals. The animation loop only
 * cycles the first 16 crystals (see lv_animimg_set_src below); these extra
 * frames exist to be pinned via CONFIG_NICE_VIEW_GEM_ANIMATION_FRAME. */
LV_IMG_DECLARE(crystal_17); /* heart        */
LV_IMG_DECLARE(crystal_18); /* shaded orb   */
LV_IMG_DECLARE(crystal_19); /* iso cube     */
LV_IMG_DECLARE(crystal_20); /* saturn       */
LV_IMG_DECLARE(crystal_21); /* moon         */
LV_IMG_DECLARE(crystal_22); /* gem          */
LV_IMG_DECLARE(crystal_23); /* bolt         */
LV_IMG_DECLARE(crystal_24); /* space invader */
LV_IMG_DECLARE(crystal_25); /* skull        */

const lv_img_dsc_t *anim_imgs[] = {
    &crystal_01, &crystal_02, &crystal_03, &crystal_04, &crystal_05, &crystal_06,
    &crystal_07, &crystal_08, &crystal_09, &crystal_10, &crystal_11, &crystal_12,
    &crystal_13, &crystal_14, &crystal_15, &crystal_16,
    /* extra static-only frames, selectable as frame 17..25 */
    &crystal_17, &crystal_18, &crystal_19, &crystal_20, &crystal_21,
    &crystal_22, &crystal_23, &crystal_24, &crystal_25,
};

void draw_animation(lv_obj_t *canvas) {
#if IS_ENABLED(CONFIG_NICE_VIEW_GEM_ANIMATION)
    lv_obj_t *art = lv_animimg_create(canvas);
    lv_obj_center(art);

    lv_animimg_set_src(art, (const void **)anim_imgs, 16);
    lv_animimg_set_duration(art, CONFIG_NICE_VIEW_GEM_ANIMATION_MS);
    lv_animimg_set_repeat_count(art, LV_ANIM_REPEAT_INFINITE);
    lv_animimg_start(art);
#else
    lv_obj_t *art = lv_img_create(canvas);

    int length = sizeof(anim_imgs) / sizeof(anim_imgs[0]);
    srand(k_uptime_get_32());
    int random_index = rand() % length;
    int configured_index = (CONFIG_NICE_VIEW_GEM_ANIMATION_FRAME - 1) % length;
    int anim_imgs_index = CONFIG_NICE_VIEW_GEM_ANIMATION_FRAME > 0 ? configured_index : random_index;

    lv_img_set_src(art, anim_imgs[anim_imgs_index]);
#endif

    lv_obj_align(art, LV_ALIGN_TOP_LEFT, 36, 0);
}